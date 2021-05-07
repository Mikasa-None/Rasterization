#include "./shader.h"


VertexAttriForShader PhongShader::vertex_shader(int faces_index, int vertex_index){
    VertexAttriForShader res;
    res.tex_uv=obj->GetTex_uv(faces_index,vertex_index);
    res.color=vec3(0,255,0);

    vec3 tri_vertex=obj->GetVertex(faces_index,vertex_index);
    res.vertex=to_vec4(tri_vertex,1.0);
    res.mvp_vertex=PerspectiveMatrix*ViewMatrix*ModelMatrix*res.vertex;
    vec4 mv_vertex=ViewMatrix*ModelMatrix*res.vertex;
    res.mv_vertex=vec3(mv_vertex.x(),mv_vertex.y(),mv_vertex.z());
    res.homo_division_mvp_vertex=vec3(res.mvp_vertex.x()/res.mvp_vertex.w(),res.mvp_vertex.y()/res.mvp_vertex.w(),res.mvp_vertex.z()/res.mvp_vertex.w());

    vec3 normal=obj->GetNormal(faces_index,vertex_index);
    vec4 Trans_normal=(ViewMatrix*ModelMatrix).inverse_transpose()*to_vec4(normal,0.0);
    res.mvInvTranspose_normal=vec3(Trans_normal.x(),Trans_normal.y(),Trans_normal.z());

    //Viewport transformation
    vec3 homovertexTmp=res.homo_division_mvp_vertex;
    float screen_x = 0.5*ViewPortWidth*(homovertexTmp.x()+1.0);
    float screen_y = 0.5*ViewPortHeight*(homovertexTmp.y()+1.0);
    float screen_z = -res.mvp_vertex.w();
    res.screen_vertex=vec3(screen_x,screen_y,screen_z);

}

vec3 PhongShader::fragment_shader(const VertexAttriForShader& vertex){
    vec3 ka = vec3(0.005, 0.005, 0.005);
    vec3 kd = vertex.color;
    vec3 ks = vec3(0.7937, 0.7937, 0.7937);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    vec3 amb_light_intensity{10, 10, 10};
    //vec3 eye_pos{0, 0, 10};
    vec3 eye_pos=camera->eye;
    float p = 150;

    vec3 point = vertex.mv_vertex;
    vec3 normal = vertex.mvInvTranspose_normal;

    vec3 color(0, 0, 0);
    for (auto& light : lights)
    {
        vec3 light_dir=light.position-point;
        vec3 view_dir=eye_pos-point;
        float r = dot(light_dir,light_dir);

        vec3 La=cwise_product(ka,amb_light_intensity);
        //std::cout<<light_dir.normalized().dot(normal.normalized())<<std::endl;
        vec3 Ld=cwise_product(kd,light.intensity/r)*std::max(0.0, dot(light_dir.normalized(),normal.normalized()) );
        vec3 h=light_dir.normalized()+view_dir.normalized();
        vec3 Ls=cwise_product(ks,light.intensity/r)*std::pow(std::max(0.0, dot(h.normalized(),normal.normalized()) ),p);
        color=color+La+Ld+Ls;
    }
    return color * 255.f;

}


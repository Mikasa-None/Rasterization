#include "./shader.h"


mat4 projection(float coff){
    mat4 m = mat4::identity();
	m[3][2] = coff;
	return m;
}

void Shader::UpdateMatrix(const vec3& scale,const vec3& rotation,const vec3& translation,int viewportWidth, int viewportHeight, float fovy, float aspect, float near, float far){
    // SetModelScaleMatrix(scale);
    // SetModelRotateMatrix(rotation);
    // SetModelTranslationMatrix(translation);

    ModelScaleMatrix=mat4_scale(scale.x(),scale.y(),scale.z());
    ModelRotateMatrix=mat4_rotate_z(rotation.z())*mat4_rotate_y(rotation.y())*mat4_rotate_x(rotation.x());
    ModelTranslationMatrix=mat4_translate(translation.x(),translation.y(),translation.z());
    ModelMatrix=ModelTranslationMatrix*ModelRotateMatrix*ModelScaleMatrix;

    //SetViewMatrix();
    //SetProjectionMatrix(fovy, aspect, near, far);
    ViewMatrix=mat4_lookat(camera.eye,camera.target,camera.up);
    ProjectionMatrix=mat4_perspective(fovy,aspect,near,far);

    std::cout<<"modelm "<<ModelMatrix<<std::endl;
    std::cout<<"viewm "<<ViewMatrix<<std::endl;
    std::cout<<"persm "<<ProjectionMatrix<<std::endl;

    ViewPortWidth=viewportWidth;
    ViewPortHeight=viewportHeight;

}




VertexAttriForShader Shader::vertex_shader(int faces_index, int vertex_index){
    VertexAttriForShader res;
    res.tex_uv=obj.GetTex_uv(faces_index,vertex_index);
    res.color=vec3(0,255,0);

    //std::cout<<res.color<<std::endl;

    vec3 tri_vertex=obj.GetVertex(faces_index,vertex_index);
    //std::cout<<"tri_vertex"<<tri_vertex<<std::endl;
    res.vertex=to_vec4(tri_vertex,1.0);
    res.mvp_vertex=ProjectionMatrix*ViewMatrix*ModelMatrix*res.vertex;
    //std::cout<<"mvp_vertex"<<res.mvp_vertex<<std::endl;
    
    vec4 mv_vertex=ViewMatrix*ModelMatrix*res.vertex;
    res.mv_vertex=vec3(mv_vertex.x(),mv_vertex.y(),mv_vertex.z());
    res.homo_division_mvp_vertex=vec3(res.mvp_vertex.x()/res.mvp_vertex.w(),res.mvp_vertex.y()/res.mvp_vertex.w(),res.mvp_vertex.z()/res.mvp_vertex.w());
    //std::cout<<"homo_division_mvp_vertex"<<res.homo_division_mvp_vertex<<std::endl;
    
    vec3 normal=obj.GetNormal(faces_index,vertex_index);
    vec4 Trans_normal=(ViewMatrix*ModelMatrix).inverse_transpose()*to_vec4(normal,0.0);
    res.mvInvTranspose_normal=vec3(Trans_normal.x(),Trans_normal.y(),Trans_normal.z());
    //std::cout<<"mvInvTranspose_normal"<<res.mvInvTranspose_normal<<std::endl;
    
    //Viewport transformation
    vec3 homovertexTmp=res.homo_division_mvp_vertex;
    float screen_x = 0.5*ViewPortWidth*(homovertexTmp.x()+1.0);
    float screen_y = 0.5*ViewPortHeight*(homovertexTmp.y()+1.0);
    // float screen_x = 0.5*ViewPortWidth*homovertexTmp.x()+0.5*ViewPortWidth;
    // float screen_y = 0.5*ViewPortHeight*homovertexTmp.y()+0.5*ViewPortHeight;
    float screen_z = -res.mvp_vertex.w();
    
    // float f1 = (50 - 0.1) / 2.0;
    // float f2 = (50 + 0.1) / 2.0;
    // vert.z() = vert.z() * f1 + f2;

    res.screen_vertex=vec3(screen_x,screen_y,screen_z);
    //std::cout<<"screen_vertex"<<res.screen_vertex<<std::endl;
    return res;

}

vec3 Shader::fragment_shader(const VertexAttriForShader& vertex){
    vec3 tex_color=obj.texture->getColor(vertex.tex_uv.x(),vertex.tex_uv.y());
    vec3 ka = vec3(0.005, 0.005, 0.005);
    vec3 kd = tex_color/255.0;
    vec3 ks = vec3(0.7937, 0.7937, 0.7937);

    auto l1 = Light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = Light{{-20, 20, 0}, {500, 500, 500}};

    std::vector<Light> lights = {l1, l2};
    vec3 amb_light_intensity{10, 10, 10};
    vec3 eye_pos=camera.eye;
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


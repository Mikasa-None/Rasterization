#include"./render.h"


int Render::get_index(int x, int y)
{
    return (ImgHeight-y)*ImgWidth + x;
}

void Render::set_color(float x, float y, const vec3& color)
{
    //old index: auto ind = point.y() + point.x() * width;
    int ind = get_index(x,y);
    for(int i=0;i<3;++i){
        framebuffer[ind][i] = color[i];
    }
    
}

bool Render::SaveOutputImg(const std::string& ImgSavePath){
    cv::Mat image(ImgWidth, ImgHeight, CV_32FC3, framebuffer.data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    //std::cout<<image.size()<<std::endl;
    //std::cout<<image<<std::endl;
    cv::imwrite(ImgSavePath,image);
    return true;

}


void Render::render_rasterizer(Shader& shader){
    int nfaces=shader.obj.GetFacesNum();
    for(int i=0;i<nfaces;++i){
        VertexAttriForShader TransedVertex[3];
        for(int j=0;j<3;++j){
            TransedVertex[j]=shader.vertex_shader(i,j);
        }
        rasterizer_triangle(TransedVertex,shader,framebuffer,zbuffer);

    }

}

void Render::rasterizer_triangle(VertexAttriForShader* trivertex,Shader& shader, 
                        std::vector<cv::Vec3f>& framebuffer,std::vector<float>& zbuffer)
    {
        float limit=std::numeric_limits<float>::max();
        float xmin=limit, xmax=-limit, ymin=limit, ymax=-limit;
        for(int i=0;i<3;i++){
            xmin=float_min(xmin,trivertex[i].screen_vertex.x());
            xmax=float_max(xmax,trivertex[i].screen_vertex.x());
            ymin=float_min(ymin,trivertex[i].screen_vertex.y());
            ymax=float_max(ymax,trivertex[i].screen_vertex.y());
        }
        //std::cout<<xmin<<std::endl;
        for(int i=(int)xmin;i<=(int)xmax;++i){
            for(int j=(int)ymin;j<=(int)ymax;++j){
                vec3 barycentric=compute_barycentric2D(i,j,trivertex[0].screen_vertex,trivertex[1].screen_vertex,trivertex[2].screen_vertex);
                float alpha=barycentric[0], beta=barycentric[1], gamma=barycentric[2];
                if(is_inside_triangle(alpha,beta,gamma)){
                    vec3 tmp(alpha/trivertex[0].mvp_vertex.w(),beta/trivertex[1].mvp_vertex.w(),gamma/trivertex[2].mvp_vertex.w());
                    float normalize_base=1.0/tmp.sum();
                    float z=normalize_base*(trivertex[0].screen_vertex.z()*tmp[0]+trivertex[1].screen_vertex.z()*tmp[1]+trivertex[2].screen_vertex.z()*tmp[2]);
                    int index=get_index(i,j);
                    if(zbuffer[index]>z){
                        zbuffer[index]=z;
                        VertexAttriForShader interpolatedVertex;
                        interpolatedVertex.color=alpha*trivertex[0].color+beta*trivertex[1].color+gamma*trivertex[2].color;
                        interpolatedVertex.mvInvTranspose_normal=alpha*trivertex[0].mvInvTranspose_normal+beta*trivertex[1].mvInvTranspose_normal+gamma*trivertex[2].mvInvTranspose_normal;
                        interpolatedVertex.mv_vertex=alpha*trivertex[0].mv_vertex+beta*trivertex[1].mv_vertex+gamma*trivertex[2].mv_vertex;
                        interpolatedVertex.tex_uv=alpha*trivertex[0].tex_uv+beta*trivertex[1].tex_uv+gamma*trivertex[2].tex_uv;

                        vec3 color;
                        color=shader.fragment_shader(interpolatedVertex);
                        //std::cout<<interpolatedVertex.color<<std::endl;
                        set_color(i,j,color);
                        
                    }
                }
            }
        }

    }
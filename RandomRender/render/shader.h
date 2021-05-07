#pragma once
#include "../utils/math.h"
#include "./transform.h"
#include "../scene/object.h"
#include "./camera.h"
#include "./light.h"


struct VertexAttriForShader{
    //public:
        //VertexAttriForShader();
        // VertexAttriForShader(vec4 _view_pos,vec3 _color,vec2 _tex_uv,vec3 _normal)
        // :view_pos(_view_pos),color(_color),tex_uv(_tex_uv),trans_normal(_normal)
        // {}
        vec4 vertex;
        vec4 mvp_vertex;
        vec3 homo_division_mvp_vertex;
        vec3 mv_vertex;
        vec3 mvInvTranspose_normal;
        vec3 screen_vertex;
        vec3 color;
        vec2 tex_uv;
        

};


class Shader{
    public:
        Shader(); 
        Shader(const Object& _obj,const Camera& _camera):obj(_obj),camera(_camera){}          
        const Object& obj;
        const Camera& camera;   
         
        mat4 ModelScaleMatrix;
        mat4 ModelRotateMatrix;
        mat4 ModelTranslationMatrix;

        mat4 ModelMatrix;
        mat4 ViewMatrix;
        mat4 ProjectionMatrix;

        int ViewPortWidth;
        int ViewPortHeight;

        void UpdateMatrix(const vec3& scale,const vec3& rotation,const vec3& translation,int viewportWidth, int viewportHeight, float fovy=60.0, float aspect=1.0, float near=-0.1, float far=-1000);


        virtual VertexAttriForShader vertex_shader(int faces_index, int vertex_index);
        virtual vec3 fragment_shader(const VertexAttriForShader& vertex);
        // VertexAttriForShader vertex_shader(int faces_index, int vertex_index);
        // vec3 fragment_shader(const VertexAttriForShader& vertex);
};

// class PhongShader:public Shader{
//     public:
//         PhongShader(Object* _obj=nullptr,Camera* _camera=nullptr):Shader(_obj,_camera){}
//         VertexAttriForShader vertex_shader(int faces_index, int vertex_index) override;
//         vec3 fragment_shader(const VertexAttriForShader& vertex) override;

// };
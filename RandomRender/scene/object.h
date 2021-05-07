#pragma once

#include "../utils/math.h"
#include "./texture.h"
#include<vector>
#include<string>



class Object{
    public:
        Object(std::string ObjFilePath);
        //virtual ~Object();
        vec3 GetVertex(int faces_index, int vertex_index)const;
        vec2 GetTex_uv(int faces_index, int vertex_index)const;
        vec3 GetNormal(int faces_index, int vertex_index)const;
        
        int GetFacesNum()const {return nfaces;}
        int GetVertexNum()const {return nvertex;}

        Texture *texture;
        bool SetTexture(Texture *tex=nullptr){
            texture=tex;
        }
    private:
        std::vector<vec3> vertex;
        std::vector<std::vector<int>> faces;
        std::vector<vec2> tex_uv;
        std::vector<vec3> normal;
        int nfaces;
        int nvertex;



};
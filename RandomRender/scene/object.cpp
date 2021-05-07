#include "./object.h"

//#include <io.h> 
#include <iostream>
#include <fstream>
#include <sstream>





Object::Object(std::string ObjFilePath){
    std::ifstream in;
	in.open(ObjFilePath, std::ifstream::in);
	if (in.fail())
	{
		printf("load model failed\n");
		return;
	}

	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) 
		{
			iss >> trash;
			vec3 v;
			for (int i = 0; i < 3; i++)
				iss >> v[i];
		
			vertex.push_back(v);
		}
		else if (!line.compare(0, 3, "vn ")) 
		{
			iss >> trash >> trash;
			vec3 n;
			for (int i = 0; i < 3; i++) 
				iss >> n[i];

			normal.push_back(n);
		}
		else if (!line.compare(0, 3, "vt ")) 
		{
			iss >> trash >> trash;
			vec2 uv;
			for (int i = 0; i < 2; i++) 
				iss >> uv[i];

			// if (is_from_mmd)
			// 	uv[1] = 1 - uv[1];
			tex_uv.push_back(uv);
		}
		else if (!line.compare(0, 2, "f ")) 
		{
			std::vector<int> f;
			int tmp[3];
			iss >> trash;
			while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) 
			{
				for (int i = 0; i < 3; i++) 
					tmp[i]--; // in wavefront obj all indices start at 1, not zero

				f.push_back(tmp[0]); f.push_back(tmp[1]); f.push_back(tmp[2]);
				
			}
			//std::cout<<f.size()<<std::endl;
			faces.push_back(f);
		}
	}
	std::cerr << "# v# " << vertex.size() << " f# " << faces.size() << " vt# " << tex_uv.size() << " vn# " << normal.size() << std::endl;

    nfaces=faces.size();
    nvertex=vertex.size();

}

vec3 Object::GetVertex(int faces_index, int vertex_index)const {
    //judge valid***********
	int index=faces[faces_index][vertex_index*3+0];
    return vertex[index];
}
vec2 Object::GetTex_uv(int faces_index, int vertex_index)const {
	int index=faces[faces_index][vertex_index*3+1];
    return tex_uv[index];
}
vec3 Object::GetNormal(int faces_index, int vertex_index)const {
	int index=faces[faces_index][vertex_index*3+2];
    return normal[index];
}
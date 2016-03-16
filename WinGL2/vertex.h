#ifndef VERTEX_H
#define VERTEX_H

struct CFace{
	int v1, v2, v3;

};



struct CVertex3{
    float x,y,z;
	
};

struct CVertex2{
    float x,y;
	
};

struct Vertex{
	CVertex3 p;
	CVertex3 n;
	CVertex2 t;
	CVertex3 tan;
	CVertex3 bin;
};

struct BoneInfo{
		float weight[4];
		int BoneID[4];
};


struct XVertex{
	CVertex3 p;
	CVertex3 n;
	CVertex2 t;
	BoneInfo b;
};

#endif
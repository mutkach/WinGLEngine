
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ilut.lib")
#pragma comment(lib,"ilu.lib")        
#pragma comment(lib,"libnoise.lib")        


// Наш главный хидер:

#include "main.h"


int triTable[256][16] =
{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

 int edgeTable[256] =

  {
  0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
  0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
  0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
  0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
  0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
  0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
  0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
  0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
  0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
  0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
  0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
  0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
  0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
  0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
  0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
  0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
  0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
  0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
  0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
  0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
  0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
  0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
  0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
  0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
  0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
  0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
  0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
  0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
  0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
  0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
  0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
  0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0

  };
 CCamera g_Camera;

GLint loc1,loc2,loc3,loc4;

std :: vector<std::vector <CVertex3>> data; //
std :: vector<std::vector <CVertex3>> normal;
std :: vector<CVertex2> texes;

std :: vector<CVertex3> vertlist;
std :: vector<CVertex3> gradlist;
std :: vector<std::vector<CFace>> fc;
CVertex3 pi[301][301][301];
CVertex3 grad;
CVertex3 grad2;
std :: deque<std :: deque <std :: vector <std :: vector <CVertex3> > > > curview; //2д-ОЧЕРЕДЬ, в которой содеражтся два массива вершин: нормалей и координат
int nom = 0;
CVector3 PreviousPosition;
CVector3 CurrentPosition;

float theta = 0;
float a[301][301][301];


float FPS;

int cubeindex = 0;
float isovalue = 0.001f;

float g_FrameInterval = 0.0f;

CTexture *Texture;
TextureImage Textures[1];

 CVertex3 VertexInterp(float isovalue, CVertex3 p1, CVertex3 p2, float valp1, float valp2)
{
   float mu;
   CVertex3 p;

   if (abs(isovalue-valp1) < 0.00001)
      return(p1);
   if (abs(isovalue-valp2) < 0.00001)
      return(p2);
   if (abs(valp1-valp2) < 0.00001)
      return(p1);
   mu = (isovalue - valp1) / (valp2 - valp1);
   p.x = p1.x + mu * (p2.x - p1.x);
   p.y = p1.y + mu * (p2.y - p1.y);
   p.z = p1.z + mu * (p2.z - p1.z);

   return(p);
}

  int toof;
HWND  g_hWnd;
RECT  g_rRect;
HDC   g_hDC;
HGLRC g_hRC;
HINSTANCE g_hInstance;



void CalculateFrameRate()
{

    static float framesPerSecond = 0.0f;    
    static float lastTime = 0.0f;           
    static char strFrameRate[50] = {0};    

    float currentTime = timeGetTime() * 0.001f;
  
    ++framesPerSecond;

    if(currentTime - lastTime > 1.0f)
    {
        lastTime = currentTime;

        FPS=framesPerSecond;

        framesPerSecond = 0;
    }
}



void GetFrameTime()
{
    static float frameTime = 0.0f;  // Время последнего кадра

    float currentTime = timeGetTime() * 0.001f;

    // Интервал времени, прошедшего с прошлого кадра
    g_FrameInterval = currentTime - frameTime;

    frameTime = currentTime;
}


void redraw(float posx, float posz){
	module :: RidgedMulti MyModule;
	module :: Perlin MyPerlin;

	 for(int i = 0; i < 42; ++i){
        for(int j = 0; j < 42; ++j){
            for(int k = 0; k < 45; ++k){
					//float bred = (noise((float)i/7.5,(float)j/7.5)+2)*5;
                    if(1) ///((i - 40)*(i - 40) + (j-40)*(j-40) + (k-40)*(k-40) - 9000)
						a[i][k][j] =  (MyModule.GetValue((i+posx)/50.0f, k/50.0f, (j+posz)/50.0f)+2)*20.0f -k - 35.0f   ; //(noise((float)i/13.5,(float)j/13.5)+2)*8 - k - 6
						//a[i][k][j] +=  (MyPerlin.GetValue(i/20.0, k/20.0, j/20.0)+2)*5.0f - 19   ; //(noise((float)i/13.5,(float)j/13.5)+2)*8 - k - 6
						


					pi[i][k][j].x = i;
					pi[i][k][j].y = k;
					pi[i][k][j].z = j;


            }
        }
    }
}

void draw(float posx, float posz, int nom) {
//test.resize(4);

vertlist.resize(12);
gradlist.resize(12);



    for(int i = 1; i  < 40; ++ i){
        for(int j = 1; j < 40; ++j){
            for(int k = 1; k < 42; ++k){
                   cubeindex = 0;
                   if (a[i + 1][k    ][j    ] < isovalue) cubeindex += 1;
                   if (a[i + 1][k    ][j + 1] < isovalue) cubeindex += 2;
                   if (a[i    ][k    ][j + 1] < isovalue) cubeindex += 4;
                   if (a[i    ][k    ][j    ] < isovalue) cubeindex += 8;
                   if (a[i + 1][k + 1][j    ] < isovalue) cubeindex += 16;
                   if (a[i + 1][k + 1][j + 1] < isovalue) cubeindex += 32;
                   if (a[i    ][k + 1][j + 1] < isovalue) cubeindex += 64;
                   if (a[i    ][k + 1][j    ] < isovalue) cubeindex += 128;
				   
									  
				   //if (edgeTable[cubeindex] == 0)
					for(int i2 = 0; i2 < 12; ++i2){
						vertlist[0].x = 0;
						vertlist[0].y = 0;
						vertlist[0].z = 0;
						gradlist[0].x = 0;
						gradlist[0].y = 0;
						gradlist[0].z = 0;

					}

				   
				   if (edgeTable[cubeindex] & 1){
					  vertlist[0] =
						 VertexInterp(isovalue, pi[i + 1][k    ][j    ], pi[i + 1][k    ][j + 1], a[i + 1][k    ][j    ], a[i + 1][k    ][j + 1]);
						 grad.x  =  a[i  ][k  ][j  ] - a[i+2][k  ][j  ];
						 grad.y  =  a[i+1][k-1][j  ] - a[i+1][k+1][j  ];
						 grad.z  =  a[i+1][k  ][j-1] - a[i+1][k  ][j+1];
						 // 0 и 1
						 grad2.x =  a[i  ][k  ][j+1] - a[i+2][k  ][j+1];
						 grad2.y =  a[i+1][k-1][j+1] - a[i+1][k+1][j+1];
						 grad2.z =  a[i+1][k  ][j  ] - a[i+1][k  ][j+2];
				      gradlist[0] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k    ][j    ], a[i + 1][k    ][j + 1]);
				   }


				   if (edgeTable[cubeindex] & 2){
					  vertlist[1] =
						 VertexInterp(isovalue, pi[i + 1][k    ][j + 1], pi[i    ][k    ][j + 1], a[i + 1][k    ][j + 1], a[i    ][k    ][j + 1]);
						 grad.x   =  a[i  ][k  ][j+1] - a[i+2][k  ][j+1];
						 grad.y   =  a[i+1][k-1][j+1] - a[i+1][k+1][j+1];
						 grad.z   =  a[i+1][k  ][j  ] - a[i+1][k  ][j+2];
						 // 1 и 2
						 grad2.x  =  a[i-1][k  ][j+1] - a[i+1][k  ][j+1];
						 grad2.y  =  a[i  ][k-1][j+1] - a[i  ][k+1][j+1];
						 grad2.z  =  a[i  ][k  ][j  ] - a[i  ][k  ][j+2];
					  gradlist[1] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k    ][j + 1], a[i    ][k    ][j + 1]);
				   }


				   if (edgeTable[cubeindex] & 4){
					  vertlist[2] =
						 VertexInterp(isovalue, pi[i    ][k    ][j + 1], pi[i    ][k    ][j    ], a[i    ][k    ][j + 1], a[i    ][k    ][j    ]);


						 grad.x    =  a[i-1][k  ][j+1] - a[i+1][k  ][j+1];
						 grad.y    =  a[i  ][k-1][j+1] - a[i  ][k+1][j+1];
						 grad.z    =  a[i  ][k  ][j  ] - a[i  ][k  ][j+2];
						 // 2 и 3
						 grad2.x   =  a[i-1][k  ][j  ] - a[i+1][k  ][j  ];
						 grad2.y   =  a[i  ][k-1][j  ] - a[i  ][k+1][j  ];
						 grad2.z   =  a[i  ][k  ][j-1] - a[i  ][k  ][j+1];
					  gradlist[2] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k    ][j + 1], a[i    ][k    ][j    ]);
				   }
				   if (edgeTable[cubeindex] & 8){
					  vertlist[3] =
						 VertexInterp(isovalue, pi[i    ][k    ][j    ], pi[i + 1][k    ][j    ], a[i    ][k    ][j    ], a[i + 1][k    ][j    ]);
						 grad.x     =  a[i-1][k  ][j  ] - a[i+1][k  ][j  ];
						 grad.y     =  a[i  ][k-1][j  ] - a[i  ][k+1][j  ];
						 grad.z     =  a[i  ][k  ][j-1] - a[i  ][k  ][j+1];
						 // 3 и 0
						 grad2.x    =  a[i  ][k  ][j  ] - a[i+2][k  ][j  ];
						 grad2.y    =  a[i+1][k-1][j  ] - a[i+1][k+1][j  ];
						 grad2.z    =  a[i+1][k  ][j-1] - a[i+1][k  ][j+1];
					  gradlist[3] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k    ][j    ], a[i + 1][k    ][j    ]);
				   }



				   if (edgeTable[cubeindex] & 16){
					  vertlist[4] =
						 VertexInterp(isovalue, pi[i + 1][k + 1][j    ], pi[i + 1][k + 1][j + 1], a[i + 1][k + 1][j    ], a[i + 1][k + 1][j + 1]);

				   		 grad.x     =  a[i  ][k+1][j  ] - a[i+2][k+1][j  ];
						 grad.y     =  a[i+1][k  ][j  ] - a[i+1][k+2][j  ];
						 grad.z     =  a[i+1][k+1][j-1] - a[i+1][k+1][j+1];
						 // 4 и 5
						 grad2.x    =  a[i  ][k+1][j+1] - a[i+2][k+1][j+1];
						 grad2.y    =  a[i+1][k  ][j+1] - a[i+1][k+2][j+1];
						 grad2.z    =  a[i+1][k+1][j  ] - a[i+1][k+1][j+2];
					  gradlist[4] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k + 1][j    ], a[i + 1][k + 1][j + 1]);
				   }



				   if (edgeTable[cubeindex] & 32){
					  vertlist[5] =
						 VertexInterp(isovalue, pi[i + 1][k + 1][j + 1], pi[i    ][k + 1][j + 1], a[i + 1][k + 1][j + 1], a[i    ][k + 1][j + 1]);
				   		 grad.x     =  a[i  ][k+1][j+1] - a[i+2][k+1][j+1];
						 grad.y     =  a[i+1][k  ][j+1] - a[i+1][k+2][j+1];
						 grad.z     =  a[i+1][k+1][j  ] - a[i+1][k+1][j+2];
						 // 5 и 6
						 grad2.x    =  a[i-1][k+1][j+1] - a[i+1][k+1][j+1];
						 grad2.y    =  a[i  ][k  ][j+1] - a[i  ][k+2][j+1];
						 grad2.z    =  a[i  ][k+1][j  ] - a[i  ][k+1][j+2];
					  gradlist[5] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k + 1][j + 1], a[i    ][k + 1][j + 1]);
				   }



				   if (edgeTable[cubeindex] & 64){
					  vertlist[6] =
						 VertexInterp(isovalue, pi[i    ][k + 1][j + 1], pi[i    ][k + 1][j    ], a[i    ][k + 1][j + 1], a[i    ][k + 1][j    ]);
				     	 grad.x     =  a[i-1][k+1][j+1] - a[i+1][k+1][j+1];
						 grad.y     =  a[i  ][k  ][j+1] - a[i  ][k+2][j+1];
						 grad.z     =  a[i  ][k+1][j  ] - a[i  ][k+1][j+2];
						 // 6 и 7
						 grad2.x    =  a[i-1][k+1][j  ] - a[i+1][k+1][j  ];
						 grad2.y    =  a[i  ][k  ][j  ] - a[i  ][k+2][j  ];
						 grad2.z    =  a[i  ][k+1][j-1] - a[i  ][k+1][j+1];
					  gradlist[6] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k + 1][j + 1], a[i    ][k + 1][j    ]);
				   }




				   if (edgeTable[cubeindex] & 128){
					  vertlist[7] =
						 VertexInterp(isovalue, pi[i    ][k + 1][j    ], pi[i + 1][k + 1][j    ], a[i    ][k + 1][j    ], a[i + 1][k + 1][j    ]);
				   		 grad.x     =  a[i-1][k+1][j  ] - a[i+1][k+1][j  ];
						 grad.y     =  a[i  ][k  ][j  ] - a[i  ][k+2][j  ];
						 grad.z     =  a[i  ][k+1][j-1] - a[i  ][k+1][j+1];
						 // 7 и 4
						 grad2.x    =  a[i  ][k+1][j  ] - a[i+2][k+1][j  ];
						 grad2.y    =  a[i+1][k  ][j  ] - a[i+1][k+2][j  ];
						 grad2.z    =  a[i+1][k+1][j-1] - a[i+1][k+1][j+1];
					  gradlist[7] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k + 1][j    ], a[i + 1][k + 1][j    ]);
				   }







				   if (edgeTable[cubeindex] & 256){
					  vertlist[8] =
						 VertexInterp(isovalue, pi[i + 1][k    ][j    ], pi[i + 1][k + 1][j    ], a[i + 1][k    ][j    ], a[i + 1][k + 1][j    ]);
				   		 grad.x     =  a[i  ][k  ][j  ] - a[i+2][k  ][j  ];
						 grad.y     =  a[i+1][k-1][j  ] - a[i+1][k+1][j  ];
						 grad.z     =  a[i+1][k  ][j-1] - a[i+1][k  ][j+1];
						 // 0 и 4
						 grad2.x    =  a[i  ][k+1][j  ] - a[i+2][k+1][j  ];
						 grad2.y    =  a[i+1][k  ][j  ] - a[i+1][k+2][j  ];
						 grad2.z    =  a[i+1][k+1][j-1] - a[i+1][k+1][j+1];
					  gradlist[8] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k    ][j    ], a[i + 1][k + 1][j    ]);
				   }





				   if (edgeTable[cubeindex] & 512){
					  vertlist[9] =
						 VertexInterp(isovalue, pi[i + 1][k    ][j + 1], pi[i + 1][k + 1][j + 1], a[i + 1][k    ][j + 1], a[i + 1][k + 1][j + 1]);
				   		 grad.x     =  a[i  ][k  ][j+1] - a[i+2][k  ][j+1];
						 grad.y     =  a[i+1][k-1][j+1] - a[i+1][k+1][j+1];
						 grad.z     =  a[i+1][k  ][j  ] - a[i+1][k  ][j+2];
						 // 1 и 5
						 grad2.x    =  a[i  ][k+1][j+1] - a[i+2][k+1][j+1];
						 grad2.y    =  a[i+1][k  ][j+1] - a[i+1][k+2][j+1];
						 grad2.z    =  a[i+1][k+1][j  ] - a[i+1][k+1][j+2];
					  gradlist[9] = 
						 VertexInterp(isovalue, grad, grad2, a[i + 1][k    ][j + 1], a[i + 1][k + 1][j + 1]);
				   }





				   if (edgeTable[cubeindex] & 1024){
					  vertlist[10] =
						 VertexInterp(isovalue, pi[i    ][k    ][j + 1], pi[i    ][k + 1][j + 1], a[i    ][k    ][j + 1], a[i    ][k + 1][j + 1]);
				   		 grad.x     =  a[i-1][k  ][j+1] - a[i+1][k  ][j+1];
						 grad.y     =  a[i  ][k-1][j+1] - a[i  ][k+1][j+1];
						 grad.z     =  a[i  ][k  ][j  ] - a[i  ][k  ][j+2];
						 // 2 и 6
						 grad2.x    =  a[i-1][k+1][j+1] - a[i+1][k+1][j+1];
						 grad2.y    =  a[i  ][k  ][j+1] - a[i  ][k+2][j+1];
						 grad2.z    =  a[i  ][k+1][j  ] - a[i  ][k+1][j+2];
					  gradlist[10] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k    ][j + 1], a[i    ][k + 1][j + 1]);
				   }




				   if (edgeTable[cubeindex] & 2048){
					  vertlist[11] =
						 VertexInterp(isovalue, pi[i    ][k    ][j    ], pi[i    ][k + 1][j    ], a[i    ][k    ][j    ], a[i    ][k + 1][j    ]);
				   		 grad.x     =  a[i-1][k  ][j  ] - a[i+1][k  ][j  ];
						 grad.y     =  a[i  ][k-1][j  ] - a[i  ][k+1][j  ];
						 grad.z     =  a[i  ][k  ][j-1] - a[i  ][k  ][j+1];
						 // 3 и 7
						 grad2.x    =  a[i-1][k+1][j  ] - a[i+1][k+1][j  ];
						 grad2.y    =  a[i  ][k  ][j  ] - a[i  ][k+2][j  ];
						 grad2.z    =  a[i  ][k+1][j-1] - a[i  ][k+1][j+1];
					  gradlist[11] = 
						 VertexInterp(isovalue, grad, grad2, a[i    ][k    ][j    ], a[i    ][k + 1][j    ]);
				   }





       
				   for (int i1=0;triTable[cubeindex][i1]!=-1;i1+=3) {
					      fc[nom].resize(fc[nom].size()+1); fc[nom][fc[nom].size()-1].v1=fc[nom].size()*3-3; fc[nom][fc[nom].size()-1].v2=fc[nom].size()*3-2; fc[nom][fc[nom].size()-1].v3=fc[nom].size()*3-1;
						  data[nom].resize(data[nom].size()+1);
						 
						  normal[nom].resize(normal[nom].size()+1);
						  data[nom][data[nom].size()-1] = vertlist[triTable[cubeindex][i1  ]];
						  data[nom][data[nom].size()-1].x +=posx;
						  data[nom][data[nom].size()-1].z +=posz;

						  
						  normal[nom][normal[nom].size()-1] = gradlist[triTable[cubeindex][i1  ]];
						  normal[nom][normal[nom].size()-1].x *=0.1f;
						  normal[nom][normal[nom].size()-1].y *=0.1f;
						  normal[nom][normal[nom].size()-1].z *=0.1f;
						  	


						  data[nom].resize(data[nom].size()+1);
						  normal[nom].resize(normal[nom].size()+1);
						 
						  data[nom][data[nom].size()-1] = vertlist[triTable[cubeindex][i1+1]];
						  data[nom][data[nom].size()-1].x +=posx;
						  data[nom][data[nom].size()-1].z +=posz;

						  normal[nom][normal[nom].size()-1] = gradlist[triTable[cubeindex][i1+1]];
						  normal[nom][normal[nom].size()-1].x *=0.1f;
						  normal[nom][normal[nom].size()-1].y *=0.1f;
						  normal[nom][normal[nom].size()-1].z *=0.1f;


						  data[nom].resize(data[nom].size()+1);
						  normal[nom].resize(normal[nom].size()+1);
						 
						  data[nom][data[nom].size()-1] = vertlist[triTable[cubeindex][i1+2]];
						  data[nom][data[nom].size()-1].x +=posx;
						  data[nom][data[nom].size()-1].z +=posz;

						  normal[nom][normal[nom].size()-1] = gradlist[triTable[cubeindex][i1+2]];
						  normal[nom][normal[nom].size()-1].x *=0.1f;
						  normal[nom][normal[nom].size()-1].y *=0.1f;
						  normal[nom][normal[nom].size()-1].z *=0.1f;



				   }
            }
        }
    }

}

GLuint v,f,f2,p;				// Дескрипторы программ и шейдеров
float lpos[4] = {1,0.5,1,0};	// Позиция источника света
float at = 0;					// Хранит угол вращения




void setShaders() {

	// Обьявление массивов строк для чтения из файлов
	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	// Создание шейдеров
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);

	// Чтение исходного кода шейдеров
	vs = textFileRead("minimal.vert");
	fs = textFileRead("minimal.frag");

	// Копируем код шейдеров
	const char * vv = vs;
	const char * ff = fs;

	// Передаём шейдерам их исходный код
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	// Освобождаем память под ненужные теперь массивы
	free(vs);free(fs);

	// Компилируем шейдеры
	glCompileShader(v);
	glCompileShader(f);


	p = glCreateProgram();

	glAttachShader(p,v);
	glAttachShader(p,f);

	// Линкуем программу
	glLinkProgram(p);
	glUseProgram(p);
	//glUseProgram(p);

	
}


void drawqueue(){
	for(int i = 0; i < 5; ++i){
		for(int k = 0; k < 5; ++k){
			drawarr(i, k);
		}
	}
}
void drawarr(int nom){
         glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3,GL_FLOAT,sizeof(CVertex3),&data[nom][0].x);
		glNormalPointer(GL_FLOAT,sizeof(CVertex3),&normal[nom][0].x);
	
		glDrawElements(GL_TRIANGLES,data[nom].size(),GL_UNSIGNED_INT, &fc[nom][0]);
		
        glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		
}
void RenderScene()
{	



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
 

	gluLookAt(g_Camera.m_vPosition.x, g_Camera.m_vPosition.y, g_Camera.m_vPosition.z,
          g_Camera.m_vView.x,     g_Camera.m_vView.y,     g_Camera.m_vView.z,
          g_Camera.m_vUpVector.x, g_Camera.m_vUpVector.y,g_Camera.m_vUpVector.z);



	GLint baseImageLoc = glGetUniformLocation(p, "baseImage");
	glUniform1i(baseImageLoc, 0);
	glBindTexture(GL_TEXTURE_2D, Textures[0].texID);
	glActiveTexture(GL_TEXTURE0 + 0);
	
	

	drawarr(0);
	
	drawarr(1);
	
	drawarr(2);
	
	drawarr(3);
	


	

	
	
	SwapBuffers(g_hDC);
}
 

 
void Init(HWND hWnd)
{
	g_hWnd = hWnd;
	GetClientRect(g_hWnd, &g_rRect);
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);
	g_Camera.PositionCamera(0, 9.5f, 6,   0, 9.5f, 0,   0, 1, 0);
	Texture = new CTexture();
	Texture->LoadTexture(IL_JPG,"image.jpg",&Textures[0]);
		glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0"))
	{
		MessageBox(NULL,"OpenGL 2.0 not supported","Error",MB_OK);
		exit(1);
	}
	data.resize(4);
	normal.resize(4);
	fc.resize(4);

	setShaders();
}
 

 
WPARAM MainLoop()
{	
	
	MSG msg;
	redraw(0, 0);
	draw(0, 0, 0);
	curview.resize(5);
	for(int i = 0; i < 5; ++i){
		curview[i].resize(5);
	}
	
	for(int i = 0; i < 5; ++i){
		for(int k = 0; k < 5; ++k){
			curview[i][k].resize(2);
			curview[i][k][0]=data[i][k];
			curview[i][k][1]=normal[i][k];
		}
	}



	toof = 1;
	
	while(1)
	{	
				
				
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			if(msg.message == WM_QUIT)
				break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{		

				
				GetFrameTime();
				g_Camera.Update();
				CurrentPosition = g_Camera.m_vPosition;
				if(floor(CurrentPosition.x/39) == floor(PreviousPosition.x/39)+1){
					data[1].clear();
					normal[1].clear();
					fc[1].clear();
					redraw(floor(CurrentPosition.x/39)*39,floor(CurrentPosition.z/39)*39);
					draw(floor(CurrentPosition.x/39)*39,floor(CurrentPosition.z/39)*39, 1);
					
					data[2].clear();
					normal[2].clear();
					fc[2].clear();
					redraw(floor(CurrentPosition.x/39)*39,(floor(CurrentPosition.z/39)+1)*39);
					draw(floor(CurrentPosition.x/39)*39,(floor(CurrentPosition.z/39)+1)*39, 2);
					
					data[3].clear();
					normal[3].clear();
					fc[3].clear();
					redraw(floor(CurrentPosition.x/39)*39,(floor(CurrentPosition.z/39)-1)*39);
					draw(floor(CurrentPosition.x/39)*39,(floor(CurrentPosition.z/39)-1)*39, 3);
	
					data[0].clear();
					normal[0].clear();
					fc[0].clear();
					redraw((floor(CurrentPosition.x/39)-1)*39,(floor(CurrentPosition.z/39))*39);
					draw((floor(CurrentPosition.x/39)-1)*39,(floor(CurrentPosition.z/39))*39, 0);

				}
		







				/*
				if(g_Camera.m_vPosition.x>19 && toof==1){
					toof = 1;
					redraw(floor(g_Camera.m_vPosition.x/19)*19,floor(g_Camera.m_vPosition.z/19)*19);

					draw(floor(g_Camera.m_vPosition.x/19)*19, floor(g_Camera.m_vPosition.z/19)*19, 1);
				}if(g_Camera.m_vPosition.z>19 && toof==1){
					toof = 1;
					redraw(floor(g_Camera.m_vPosition.x/19)*19,floor(g_Camera.m_vPosition.z/19)*19);

					draw(floor(g_Camera.m_vPosition.x/19)*19, floor(g_Camera.m_vPosition.z/19)*19, 2);
				}
				*/
		
				PreviousPosition = CurrentPosition;
				g_Camera.SetViewByMouse();
				RenderScene();
        }
	}
 
	DeInit();
 
	return(msg.wParam);
}
 
///////////////////////////////////////////////////////////////
//
//			Обработка сообщений windows
//
///////////////////////////////////////////////////////////////
 
LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG    lRet = 0;
    PAINTSTRUCT    ps;
 
    switch (uMsg)
	{
    case WM_SIZE:		// Если изменён размер окна
 
		SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));// LoWord=Width, HiWord=Height
		GetClientRect(hWnd, &g_rRect);		// получаем window rectangle
        break;
 
	case WM_PAINT:			// Если нужно перерисовать сцену
		BeginPaint(hWnd, &ps);	// Иниц. paint struct
		EndPaint(hWnd, &ps);	// EndPaint, подчищаем
		break;
 
	case WM_KEYDOWN:	// Это сообщение означает, что нажата клавиша на клавиатуре.
				// Сама клавиша передаётся в параметре wParam
		switch(wParam)
		{
			case VK_ESCAPE:			// Если нажат ESCAPE
				PostQuitMessage(0);	// Выходим
				break;
		}
		break;
 
    case WM_CLOSE:		// Если окно было закрыто
        PostQuitMessage(0);	// Выходим
        break;
 
    default:		// Return по умолчанию
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }
 
    return lRet;
}

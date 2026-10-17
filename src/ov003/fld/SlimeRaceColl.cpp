#include "ov003/fld/SlimeRaceColl.hpp"
#include "main/dss/DssUtils.hpp"
#include "nnsys/fnd.hpp"

namespace race {

int coll_init(COLL_HEADER* header, NNSFndAllocator* allocator)
{
    COLL_LINE* id_list;
    int i;
    if (header == NULL) {
        return 1;
    }
    if ((unsigned int)header->poly < (unsigned int)header) {
        id_list = (COLL_LINE*)((unsigned int)header + (unsigned int)header->ext_data);
        header->ext_data = (COLL_EXT_DATA*)func_0207ebcc(allocator, 8);
        if (header->ext_data == NULL) {
            return 0;
        }
        header->ext_data->id_list = id_list;
        header->ext_data->ext_num = 0;
        header->poly = (COLL_POLY*)((unsigned int)header + (unsigned int)header->poly);
        header->x0 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->x0);
        header->x1 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->x1);
        header->y0 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->y0);
        header->y1 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->y1);
        header->z0 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->z0);
        header->z1 = (COLL_LINE*)((unsigned int)header + (unsigned int)header->z1);
        header->check = (char*)((unsigned int)header + (unsigned int)header->check);
        header->check2 = (char*)((unsigned int)header + (unsigned int)header->check2);
    }
    for (i = 0; i < header->poly_size; i++) {
        header->poly[i].flag = 0;
    }
    return 1;
}

fx32 coll_GetCrossPoint3D(VecFx32* point, VecFx32* vertex, VecFx32* normal, VecFx32* cross)
{
    VecFx32 vec;
    fx32 dot;
    fx32 len;
    func_0208a1dc(vertex, point, &vec);
    dot = func_0208a210(normal, &vec);
    if (-normal->y == 0) {
        cross->x = point->x;
        cross->y = point->y;
        cross->z = point->z;
        return 0x7fffffff;
    }
    len = FX_Divide(dot, -normal->y);
    cross->x = point->x;
    cross->y = point->y - len;
    cross->z = point->z;
    return len;
}

int coll_CheckPolyPointOne(COLL_POLY* poly, VecFx32* point)
{
    if (((fx64)poly->vertex[1].x - poly->vertex[0].x) * ((fx64)point->z - poly->vertex[0].z) - ((fx64)point->x - poly->vertex[0].x) * ((fx64)poly->vertex[1].z - poly->vertex[0].z) > 0) {
        return 0;
    }
    if (((fx64)poly->vertex[2].x - poly->vertex[1].x) * ((fx64)point->z - poly->vertex[1].z) - ((fx64)point->x - poly->vertex[1].x) * ((fx64)poly->vertex[2].z - poly->vertex[1].z) > 0) {
        return 0;
    }
    if ((poly->type & 1) != 1) {
        if (((fx64)poly->vertex[0].x - poly->vertex[2].x) * ((fx64)point->z - poly->vertex[2].z) - ((fx64)point->x - poly->vertex[2].x) * ((fx64)poly->vertex[0].z - poly->vertex[2].z) > 0) {
            return 0;
        }
    } else {
        if (((fx64)poly->vertex[3].x - poly->vertex[2].x) * ((fx64)point->z - poly->vertex[2].z) - ((fx64)point->x - poly->vertex[2].x) * ((fx64)poly->vertex[3].z - poly->vertex[2].z) > 0) {
            return 0;
        }
        if (((fx64)poly->vertex[0].x - poly->vertex[3].x) * ((fx64)point->z - poly->vertex[3].z) - ((fx64)point->x - poly->vertex[3].x) * ((fx64)poly->vertex[0].z - poly->vertex[3].z) > 0) {
            return 0;
        }
    }
    return 1;
}

int coll_CheckPolyPoint(COLL_POLY* poly, VecFx32* point)
{
    VecFx32 point1;
    if (race::coll_CheckPolyPointOne(poly, point)) {
        return 1;
    }
    point1 = *point;
    point1.z += 0xcc;
    if (race::coll_CheckPolyPointOne(poly, &point1)) {
        return 1;
    }
    point1 = *point;
    point1.x -= 0xcc;
    point1.z -= 0xcc;
    if (race::coll_CheckPolyPointOne(poly, &point1)) {
        return 1;
    }
    point1 = *point;
    point1.x += 0xcc;
    point1.z -= 0xcc;
    if (race::coll_CheckPolyPointOne(poly, &point1)) {
        return 1;
    }
    return 0;
}

int coll_CheckLinePoint(const VecFx32* posP, fx32 r, const VecFx32* posA, const VecFx32* posB, const VecFx32* nml, VecFx32* cross)
{
    VecFx32 vec;
    VecFx32 vec1;
    VecFx32 vec2;
    VecFx32 vec3;
    fx32 rr;
    fx32 t;
    if (posA->y > posP->y || posB->y < posP->y - r) {
        return 0;
    }
    rr = FX_Mul(r, r);
    vec.x = posB->x - posA->x;
    vec.z = posB->z - posA->z;
    if (vec.x == 0 && vec.z == 0) {
        return 0;
    }
    vec1.x = posP->x - posA->x;
    vec1.y = 0;
    vec1.z = posP->z - posA->z;
    t = FX_Divide(FX_Mul(vec.x, vec1.x) + FX_Mul(vec.z, vec1.z), FX_Mul(vec.x, vec.x) + FX_Mul(vec.z, vec.z));
    if (t < 0) {
        if (FX_Mul(vec1.x, vec1.x) + FX_Mul(vec1.z, vec1.z) <= rr) {
            *cross = *posA;
        } else {
            return 0;
        }
        if (FX_Mul(vec1.x, nml->x) + FX_Mul(vec1.z, nml->z) < 0) {
            return 0;
        }
    } else if (t > 0x1000) {
        func_0208a1dc(posP, posB, &vec2);
        if (FX_Mul(vec2.x, vec2.x) + FX_Mul(vec2.z, vec2.z) <= rr) {
            *cross = *posB;
        } else {
            return 0;
        }
        if (FX_Mul(vec2.x, nml->x) + FX_Mul(vec2.z, nml->z) < 0) {
            return 0;
        }
    } else {
        vec2.x = FX_Mul(t, vec.x);
        vec2.y = 0;
        vec2.z = FX_Mul(t, vec.z);
        func_0208a1a8(posA, &vec2, cross);
        cross->y = posP->y;
        func_0208a1dc(&vec2, &vec1, &vec3);
        if (FX_Mul(vec3.x, vec3.x) + FX_Mul(vec3.z, vec3.z) > rr) {
            return 0;
        }
        if (FX_Mul(vec3.x, nml->x) + FX_Mul(vec3.z, nml->z) > 0) {
            return 0;
        }
    }
    return 1;
}

int coll_CheckWallId(COLL_HEADER* header, VecFx32* center, fx32 r)
{
    int j;
    int i;
    VecFx32 ret;
    if (header == NULL) {
        return -1;
    }
    for (i = 0; i < header->id_size; i++) {
        j = header->ext_data->id_list[i].poly_id;
        if (race::coll_CheckLinePoint(center, r, &header->poly[j].bbox[0], &header->poly[j].bbox[1], &header->poly[j].normal, &ret)) {
            if (header->poly[j].id != -1) {
                return header->poly[j].id;
            }
        }
    }
    for (j = 0; j < header->ext_data->ext_num; j++) {
        if (race::coll_CheckLinePoint(center, r, &header->ext_data->ext_coll[j].bbox[0], &header->ext_data->ext_coll[j].bbox[1], &header->ext_data->ext_coll[j].normal, &ret)) {
            if (header->ext_data->ext_coll[j].id != -1) {
                return header->ext_data->ext_coll[j].id;
            }
        }
    }
    {
        VecFx32 point = *center;
        j = race::coll_SearchFloorPoly(header, &point, r, &ret);
        if (j != -1 && header->poly[j].id != -1) {
            return header->poly[j].id;
        }
    }
    return -1;
}

int coll_GetCollLinePosL(COLL_LINE* line, int size, short val)
{
    int step = size / 2;
    int pos = step;
    do {
        if (val > line[pos].val) {
            if (step == -1) {
                return pos + 1;
            }
            if (step < -1) {
                step = ((step ^ -1) + 1) >> 1;
            } else {
                step >>= 1;
                if (step == 0) {
                    step = 1;
                }
            }
        } else if (val < line[pos].val) {
            if (step == 1) {
                return pos;
            }
            if (step > 1) {
                step = ((step ^ -1) + 2) >> 1;
            } else {
                step = (step + 1) >> 1;
                if (step == 0) {
                    step = -1;
                }
            }
        } else {
            step = -1;
        }
        pos += step;
        if (pos < 0) {
            return 0;
        }
    } while (pos < size);
    return -1;
}

int coll_GetCollLinePosG(COLL_LINE* line, int size, short val)
{
    int step = size / 2;
    int pos = step;
    do {
        if (val < line[pos].val) {
            if (step == -1) {
                return pos + 1;
            }
            if (step < -1) {
                step = ((step ^ -1) + 1) >> 1;
            } else {
                step >>= 1;
                if (step == 0) {
                    step = 1;
                }
            }
        } else if (val > line[pos].val) {
            if (step == 1) {
                return pos;
            }
            if (step > 1) {
                step = ((step ^ -1) + 2) >> 1;
            } else {
                step = (step + 1) >> 1;
                if (step == 0) {
                    step = -1;
                }
            }
        } else {
            step = -1;
        }
        pos += step;
        if (pos < 0) {
            return 0;
        }
    } while (pos < size);
    return -1;
}

int coll_PreSearchFloorPoly(COLL_HEADER* header, VecFx32* point)
{
    char* ptr;
    unsigned short* cl_ptr;
    unsigned short* cl_end;
    int size;
    int ret;
    short x;
    short z;
    if (header == NULL) {
        return 0;
    }
    size = header->poly_size;
    x = point->x >> 7;
    z = point->z >> 7;
    ptr = header->check;
    MI_CpuSet(ptr, 0, size);
    ret = race::coll_GetCollLinePosL(header->x0, size, x);
    if (ret < 0) {
        return 0;
    }
    cl_ptr = &header->x0[ret].poly_id;
    cl_end = &header->x0[size].poly_id;
    while (cl_ptr != cl_end) {
        ptr[*cl_ptr] |= 1;
        cl_ptr += 2;
    }
    ret = race::coll_GetCollLinePosG(header->x1, size, x);
    if (ret < 0) {
        return 0;
    }
    cl_ptr = &header->x1[ret].poly_id;
    cl_end = &header->x1[size].poly_id;
    while (cl_ptr != cl_end) {
        ptr[*cl_ptr] |= 2;
        cl_ptr += 2;
    }
    ret = race::coll_GetCollLinePosL(header->z0, size, z);
    if (ret < 0) {
        return 0;
    }
    cl_ptr = &header->z0[ret].poly_id;
    cl_end = &header->z0[size].poly_id;
    while (cl_ptr != cl_end) {
        ptr[*cl_ptr] |= 4;
        cl_ptr += 2;
    }
    ret = race::coll_GetCollLinePosG(header->z1, size, z);
    if (ret < 0) {
        return 0;
    }
    cl_ptr = &header->z1[ret].poly_id;
    cl_end = &header->z1[size].poly_id;
    while (cl_ptr != cl_end) {
        ptr[*cl_ptr] |= 8;
        cl_ptr += 2;
    }
    return 1;
}

int coll_SearchFloorPoly(COLL_HEADER* header, VecFx32* point, fx32 height, VecFx32* ret)
{
    char* ptr;
    int no;
    int size;
    int i;
    fx32 min;
    fx32 len;
    VecFx32 cross;
    VecFx32 org_point;
    min = 0x7fffffff;
    if (header == NULL) {
        return -1;
    }
    if (point == NULL) {
        return -1;
    }
    if (ret != NULL) {
        *ret = *point;
    }
    org_point = *point;
    if (header->check_point[0].x > point->x || header->check_point[0].z > point->z || header->check_point[1].x < point->x || header->check_point[1].z < point->z) {
        header->check_point[0] = *point;
        header->check_point[1] = *point;
        race::coll_PreSearchFloorPoly(header, &org_point);
    }
    size = header->floor_poly_size;
    ptr = header->check;
    for (i = 0; i < size; i++) {
        if (header->poly[i].flag & 1) {
            ptr++;
        } else if ((*ptr++ & 0xf) == 0xf || (header->poly[i].flag & 2)) {
            if (race::coll_CheckPolyPoint(&header->poly[i], &org_point)) {
                len = race::coll_GetCrossPoint3D(&org_point, &header->poly[i].vertex[0], &header->poly[i].normal, &cross);
                if (len >= 0 && min > len) {
                    min = len;
                    no = i;
                    if (ret != NULL) {
                        *ret = cross;
                    }
                }
            }
        }
    }
    if (min == 0x7fffffff) {
        return -1;
    }
    if (ret != NULL) {
        ret->y += height;
    }
    return no;
}

}  // namespace race

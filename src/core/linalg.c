#include "linalg.h"

#include <math.h>

// Mat2

Mat2 mat2_rotation(const float angle) {
    const float c = cosf(angle);
    const float s = sinf(angle);
    Mat2 result;
    result.x1 = c;
    result.x2 = s;
    result.y1 = -s;
    result.y2 = c;
    return result;
}

Vec2 mat2_mul_vec2(const Mat2 a, const Vec2 b) {
    Vec2 result;
    result.x = a.x1 * b.x + a.y1 * b.y;
    result.y = a.x2 * b.x + a.y2 * b.y;
    return result;
}

// Vec2

Vec2 vec2_add(Vec2 a, const Vec2 b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vec2 vec2_sub(Vec2 a, const Vec2 b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Vec2 vec2_scale(Vec2 a, const float s) {
    a.x *= s;
    a.y *= s;
    return a;
}

float vec2_len(const Vec2 a) {
    return sqrtf(vec2_dot(a, a));
}

float vec2_dot(const Vec2 a, const Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 vec2_norm(Vec2 a) {
    const float len = vec2_len(a);
    if (len == 0) {
        return a;
    }

    a.x = a.x / len;
    a.y = a.y / len;
    return a;
}

Vec2 vec2_rotate(const Vec2 a, const float angle) {
    const Mat2 mat = mat2_rotation(angle);
    return mat2_mul_vec2(mat, a);
}
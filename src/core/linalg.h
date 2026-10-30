#ifndef RACER_LINALG_H
#define RACER_LINALG_H

typedef struct {
    float x1, y1;
    float x2, y2;
} Mat2;

typedef struct {
    float x;
    float y;
} Vec2;

// Mat2

Mat2 mat2_rotation(float angle);
Vec2 mat2_mul_vec2(Mat2 a, Vec2 b);

// Vec2

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_scale(Vec2 a, float s);
float vec2_len(Vec2 a);
float vec2_dot(Vec2 a, Vec2 b);
Vec2 vec2_norm(Vec2 a);
Vec2 vec2_rotate(Vec2 a, float angle);

#endif // RACER_LINALG_H

#version 450 core
layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 value;

uniform float zoom;
uniform float side;
uniform float updown;
out vec2 val_me;

vec3 perspective(vec3 pos)
{
    float aspect_ratio = 800.f / 800.f;
    float half_fov = 60.f / 2.f;
    float fov = tan(radians(half_fov));
    
    float near = 0.01f;
    float far = 1000.f;
    float range = far - near;

    vec3 persp;
    persp.x = pos.x / -pos.z;
    persp.y = pos.y / -pos.z;
    //Trasforming Z in NDC range [-1, 1] where near = -1 and far = 1
    //persp.z = ((pos.z - near) / range) * 2 + 1;
    persp.z = ((-pos.z - near) / range) * 2 - 1;

    persp.x = persp.x / (fov * aspect_ratio);
    persp.y = persp.y / fov;

    return persp;
}

vec3 scale(vec3 vec, float scale)
{
    return vec * scale;
}

void main() {
    val_me = value;
    vec3 vertex = vert_pos;
    vertex = scale(vertex, zoom * 100);
    vertex.z -= 400;
    vertex.y += updown;
    vertex.x += side;
    vec3 fixed_vert = perspective(vertex);
    gl_Position = vec4(fixed_vert, 1.0);
}
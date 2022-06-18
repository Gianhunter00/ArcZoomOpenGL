#version 450 core
out vec4 frag_color;

in vec2 val_me;
void main() {
    float R = 1.0; 
    float R2 = 0.5; 
    float dist = sqrt(dot(val_me,val_me));
    if(false)
    {
        // circle (with one triangle it will be an arc (half a circle))
        if (dist >= R || dist <= R2)
         { discard; }
        frag_color = vec4(0.0, 0.0, 1.0, 1.0); //Blue color
    }
    else
    {
        //arc (using 2 triangle u can make an arc with this function, based on the arc size you have to adjust the value)
        float sm = smoothstep(R,R-0.01,dist);
        float sm2 = smoothstep(R2,R2+0.01,dist);
        float alpha = sm*sm2;
        float S = 0.75;
        float g = val_me.x / dist;
        float ds = (1.0-pow(g,16.0))*0.005;
        float sector = 0.5+g/2.0;
        float s = smoothstep(S, S+ds, sector);
        frag_color = vec4(0.0, 0.0, 1.0, alpha*s);
    }
}

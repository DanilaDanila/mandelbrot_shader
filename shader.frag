#version 120

uniform int depth;
uniform int resolution;
uniform float pos_x;
uniform float pos_y;
uniform float zoom;

float getColor(float x, float y)
{
    int _depth = depth;
    float n = 0.0;
    float i = 0.0;

    while(((n*n + i*i) < 4.0) && (_depth >= 0))
    {
        float new_n = n*n - i*i;
        float new_i = 2.0*n*i;

        n = new_n + x/zoom + pos_x;
        i = new_i + y/zoom + pos_y;
        _depth--;
    }

    return (_depth >= 0)?((depth - _depth)/float(depth)):0.0;
}

void main(void)
{
    float a = depth + resolution + pos_x + pos_y + zoom;
    float x = 2.0*gl_FragCoord.x/resolution - 1.0;
    float y = 2.0*gl_FragCoord.y/resolution - 1.0;
    float color = getColor(x, y);
   
    gl_FragColor = (x*x + y*y <= 0.00001)?vec4(1.0, 0.0, 0.0, 1.0):vec4(color, color, color, 1.0);
}

#version 330

smooth in vec3 tex_coords;
smooth in vec3 position;
smooth in vec3 camera;

uniform sampler3D volume;

uniform float red_min, green_min, blue_min;
uniform float red_max, green_max, blue_max;

uniform vec3 light_pos;

out vec4 frag_color;

vec4 transfer_function(float red_color) {
    vec4 rgba = vec4(0, 0, 0, 0);

    if (red_color >= red_min && red_color <= red_max) rgba += vec4(red_color, 0, 0, red_color/3);
    if (red_color >= green_min && red_color <= green_max) rgba += vec4(0, red_color, 0, red_color/3);
    if (red_color >= blue_min && red_color <= blue_max) rgba += vec4(0, 0, red_color, red_color/3);

    return rgba;
}

vec3 compute_normal(vec3 curr_pos) {
    float dx = 1.0 / 256;

    float negx  = texture(volume, vec3(curr_pos.x - dx, curr_pos.y, curr_pos.z)).x;
    float posx  = texture(volume, vec3(curr_pos.x + dx, curr_pos.y, curr_pos.z)).x;
    float negy  = texture(volume, vec3(curr_pos.x, curr_pos.y - dx, curr_pos.z)).x;
    float posy  = texture(volume, vec3(curr_pos.x, curr_pos.y + dx, curr_pos.z)).x;
    float negz  = texture(volume, vec3(curr_pos.x, curr_pos.y, curr_pos.z - dx)).x;
    float posz  = texture(volume, vec3(curr_pos.x, curr_pos.y, curr_pos.z + dx)).x;

    return normalize(vec3(negx - posx, negy - posy, negz - posz));
}

void main (void) {
    vec3 pos = tex_coords.xyz;
    vec3 dir = normalize(position - camera);
    vec3 light_color = vec3(1, 1, 1);

    float steps = 512;
    float alpha_threshold = 0.95f;

    vec3 volExtentMin = vec3(0.0);
    vec3 volExtentMax = vec3(1.0);

    vec4 current_color;
    vec4 acc_color = vec4(0, 0, 0, 0);

    float ka = 0.2, kd = 0.7, ks = 1.2;
    float specularN = 10.0;

    for (int i = 0; i < steps; i++) {
        current_color = transfer_function(texture(volume, pos).x);

        vec3 norm = compute_normal(pos);
        vec3 light_dir = normalize(light_pos - (pos - vec3(0.5)));

        float diffuse = max(dot(norm, light_dir), 0.0);

        vec3 light_reflect = reflect(-light_dir, norm);
        float specular = pow( max(dot(dir, light_reflect), 0.0) , specularN );

        vec3 diffuse_color = diffuse * light_color;
        vec3 specular_color = specular * light_color;

        vec3 phong = ka * light_color + kd * diffuse_color + ks * specular_color;
        current_color.rgb = phong * current_color.rgb;

        acc_color.rgb += (1.0 - acc_color.a) * current_color.rgb * current_color.a;
        acc_color.a += (1.0 - acc_color.a) * current_color.a;

        pos += dir * vec3(1.0 / steps);

        vec3 temp1 = sign(pos - volExtentMin);
        vec3 temp2 = sign(volExtentMax - pos);
        float inside = dot(temp1, temp2);
        if (inside < 3.0) break;

        if (acc_color.a >= alpha_threshold) break;
    }

    frag_color = acc_color;
}

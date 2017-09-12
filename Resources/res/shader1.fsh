#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main() {
    if (v_texCoord.x > 0.5) {
        gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0) * texture2D(CC_Texture0, v_texCoord);

    } else {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0) * texture2D(CC_Texture0, v_texCoord);
    }
}
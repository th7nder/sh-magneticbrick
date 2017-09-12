#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main() {
    if (v_texCoord.y > 0.5) {
        gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0) * texture2D(CC_Texture0, v_texCoord);
        
    } else {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * texture2D(CC_Texture0, v_texCoord);
    }
}
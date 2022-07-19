// Largely taken from http://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/

#shader vertex
#version 330 core

uniform mat4 uCameraMatrix;

//XY Plane [-1,-1,0] to [1,1,0]
const vec3 gridPlane[6] = vec3[6](
	vec3(1,1,0), vec3(-1,-1,0), vec3(-1,1,0), 
	vec3(-1,-1,0), vec3(1,1,0), vec3(1,-1,0)
);

out vec3 vNearPoint;
out vec3 vFarPoint;


// Convert clip-space points to world-space based on cameraMat
vec3 UnprojectPoint(float x, float y, float z, mat4 cameraMat){
	mat4 camInv = inverse(cameraMat);
	vec4 unprojectedPoint = camInv * vec4(x, y, z, 1.0);
	return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
	vec3 p = gridPlane[gl_VertexID];
	vNearPoint = UnprojectPoint(p.x, p.y, 0.0, uCameraMatrix).xyz; // unprojecting on the near plane
    vFarPoint = UnprojectPoint(p.x, p.y, 1.0, uCameraMatrix).xyz; // unprojecting on the far plane

    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}

#shader fragment
#version 330 core

uniform mat4 uCameraMatrix;
uniform vec3 uViewPos;

uniform float uGridOpacity = 0.5f;
uniform float uGridFalloff = 1.0f;

in vec3 vNearPoint;
in vec3 vFarPoint;

out vec4 color;


vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, uGridOpacity - min(line, 1.0));
    // z axis
    if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
        color.z = 1.0;
    // x axis
    if(fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
        color.x = 1.0;
    return color;
}

//Returns depth between 0 to 1
float computeDepth(vec3 pos) {
    vec4 clip_space_pos = uCameraMatrix * vec4(pos.xyz, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w);
	return 0.5 * (clip_space_depth + 1); //convert from (-1)-1 to 0-1 
}

float fadingFalloff(float fade){
    return min(max(fade*fade -uGridFalloff,0),1);
}

void main()
{
	float t = -vNearPoint.y / (vFarPoint.y - vNearPoint.y); //Find Intersection with y=0
	vec3 fragPos3D = vNearPoint + t * (vFarPoint - vNearPoint);

	float depth = computeDepth(fragPos3D);
	gl_FragDepth = depth;

    vec3 viewDir = normalize(fragPos3D - uViewPos);
    float fading = abs(dot(viewDir, vec3(0,1,0))); //UP Vector

	color = grid(fragPos3D, 10, true) * float(t > 0);
	color.a *= fadingFalloff(fading);
}

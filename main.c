#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include <stdio.h>

#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
  return canvas.width;
});

EM_JS(int, canvas_get_height, (), {
  return canvas.height;
});

EM_BOOL emscripten_window_resized_callback(int eventType, const void *reserved, void *userData)
{
	printf("here %d %d\n", canvas_get_width(), canvas_get_height());
	double r=drand48();
	double g=drand48();
	double b=drand48();
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0.0, 0.0, 0.0);
	GLfloat vertices[6] = {0,0,0,  50,50,0}; // x, y, z
	GLubyte indices[2] = {0, 1};

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, /*normalized=*/GL_TRUE, 0, vertices);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices);
	glDisableVertexAttribArray(0);

	return EM_TRUE;
}
//void loop_fn(void *arg)
EM_BOOL loop_fn(double time, void *arg)
{
	//double r=lrand48()%256;
	//double g=lrand48()%256;
	//double b=lrand48()%256;
	//glClearColor(r, g, b, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	return EM_TRUE;
}

int main(){
	EmscriptenWebGLContextAttributes attr;
	emscripten_webgl_init_context_attributes(&attr);

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
	emscripten_webgl_make_context_current(ctx);

	EmscriptenFullscreenStrategy strategy;
	strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF; // DPI-independent "pixel"
	strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
	strategy.canvasResizedCallback = emscripten_window_resized_callback;
	emscripten_enter_soft_fullscreen("canvas", &strategy);

	emscripten_request_animation_frame_loop(loop_fn, 0);
	//emscripten_set_main_loop_arg(loop_fn, NULL, /*fps=*/-1, /*simulate_infinite_loop=*/1);
	return 0;
}

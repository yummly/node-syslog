#ifndef syslog_h
#define syslog_h

#include <node.h>
#include <node_object_wrap.h>
#include <node_version.h>
#include <v8.h>
#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

namespace node {


class Syslog : ObjectWrap {
    public:
	static void Initialize ( v8::Handle<v8::Object> target);
	    
    protected:
	static v8::Persistent<v8::FunctionTemplate> constructor_template;
	static v8::Handle<v8::Value> init   (const v8::Arguments& args);
	static v8::Handle<v8::Value> log (const v8::Arguments& args);
	static v8::Handle<v8::Value> setMask (const v8::Arguments& args);
	static v8::Handle<v8::Value> destroy (const v8::Arguments& args);
	
	Syslog () : ObjectWrap() {
	};
	
	~Syslog (){
		if (loop_) {
			uv_stop(loop_);
			uv_loop_delete(loop_);
			loop_ = NULL;
		}
	};


    private:
	static void open(int, int);
	static void close();
	static bool connected_;
	static char name[1024];
	static uv_loop_t *loop_;
};

}  // namespace node
#endif // syslog_h

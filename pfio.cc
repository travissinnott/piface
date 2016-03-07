#include <node.h>
#include <v8.h>
#include "pfio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <sys/ioctl.h>

using namespace v8;

void PfioInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
	pfio_init();
}

void PfioDeinit(const v8::FunctionCallbackInfo<v8::Value>& args) {
	pfio_deinit();
}

void PfioDigitalRead(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	uint8_t pin = Integer::New(isolate, args[0]->IntegerValue())->Value();
	uint8_t val = pfio_digital_read(pin);
	args.GetReturnValue().Set(val);
}

void PfioDigitalWrite(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	uint8_t pin = Integer::New(isolate, args[0]->IntegerValue())->Value();
	uint8_t val = Integer::New(isolate, args[1]->IntegerValue())->Value();
	pfio_digital_write(pin, val);
}

void PfioReadInput(const v8::FunctionCallbackInfo<v8::Value>& args) {
	uint8_t val = pfio_read_input();
	args.GetReturnValue().Set(val);
}

void PfioReadOutput(const v8::FunctionCallbackInfo<v8::Value>& args) {
	uint8_t val = pfio_read_output();
	args.GetReturnValue().Set(val);
}

void PfioWriteOutput(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	uint8_t val = Integer::New(isolate, args[0]->IntegerValue())->Value();
	pfio_write_output(val);
}

void init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "init", PfioInit);
	NODE_SET_METHOD(exports, "deinit", PfioDeinit);
	NODE_SET_METHOD(exports, "digital_read", PfioDigitalRead);
	NODE_SET_METHOD(exports, "digital_write", PfioDigitalWrite);
	NODE_SET_METHOD(exports, "read_input", PfioReadInput);
	NODE_SET_METHOD(exports, "read_output", PfioReadOutput);
	NODE_SET_METHOD(exports, "write_output", PfioWriteOutput);
}

NODE_MODULE(pfio, init);
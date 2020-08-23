#include <string>

#include <grpcpp/grpcpp.h>
#include "stringreverse.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using stringreverse::StringReverse;
using stringreverse::StringRequest;
using stringreverse::StringReply;

class StringReverseClient {
    public:
        StringReverseClient(std::shared_ptr<Channel> channel) : stub_(StringReverse::NewStub(channel)) {}

    std::string sendRequest(std::string a) {
        StringRequest request;

        request.set_a(a);

        StringReply reply;

        ClientContext context;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok()){
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return "Error";
        }
    }

    private:
        std::unique_ptr<StringReverse::Stub> stub_;
};

void RunClient() {
    std::string target_address("0.0.0.0:50051");
    StringReverseClient client(
        grpc::CreateChannel(
            target_address, 
            grpc::InsecureChannelCredentials()
        )
    );

    std::string response;
    std::string a ="shradha";

    response = client.sendRequest(a);
    std::cout << "Original string: "<< a << std::endl;
    std::cout << "Reversed string: "<< response << std::endl;
}

int main(int argc, char* argv[]){
    RunClient();

    return 0;
}
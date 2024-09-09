#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "text_update.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using text_update::TextUpdateRequest;
using text_update::TextUpdateResponse;
using text_update::TextUpdateService;

class TextUpdateClient {
 public:
  TextUpdateClient(std::shared_ptr<Channel> channel) : stub_(TextUpdateService::NewStub(channel)) {}

  void StreamTextUpdates(const std::string& client_id) {
    ClientContext context;
    TextUpdateRequest request;
    request.set_client_id(client_id);

    std::unique_ptr<grpc::ClientReader<TextUpdateResponse>> reader(
        stub_->StreamTextUpdates(&context, request));

    TextUpdateResponse response;
    while (reader->Read(&response)) {
      std::cout << "Received update: " << response.updated_text() << std::endl;
    }

    Status status = reader->Finish();
    if (status.ok()) {
      std::cout << "StreamTextUpdates rpc succeeded." << std::endl;
    } else {
      std::cout << "StreamTextUpdates rpc failed." << std::endl;
    }
  }

 private:
  std::unique_ptr<TextUpdateService::Stub> stub_;
};

int main(int argc, char** argv) {
  TextUpdateClient client(
      grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  client.StreamTextUpdates("Client1");
  return 0;
}

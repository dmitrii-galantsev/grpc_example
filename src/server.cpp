// Below has been written with help from https://claude.ai/ Claude 3.5 Sonnet

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "text_update.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using text_update::TextUpdateRequest;
using text_update::TextUpdateResponse;
using text_update::TextUpdateService;

class TextUpdateServiceImpl final : public TextUpdateService::Service {
 public:
  Status StreamTextUpdates(ServerContext* context, const TextUpdateRequest* request,
                           ServerWriter<TextUpdateResponse>* writer) override {
    std::cout << "Received request from client: " << request->client_id() << std::endl;

    for (int i = 0; i < 5; ++i) {
      TextUpdateResponse response;
      response.set_updated_text("Update " + std::to_string(i + 1) + " for " + std::to_string(request->client_id()));
      response.set_updated_number(request->client_id() * 1000);

      if (!writer->Write(response)) {
        return Status::CANCELLED;
      }

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  TextUpdateServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}

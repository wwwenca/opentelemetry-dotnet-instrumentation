#1) ./build.sh
#2) mkdir $HOME/.otel-dotnet-auto
#3) cp -R ./bin/tracer-home/* $HOME/.otel-dotnet-auto

 . $HOME/.otel-dotnet-auto/instrument.sh

export ASPNETCORE_URLS="https://localhost:7061;http://localhost:5061"
export ASPNETCORE_ENVIRONMENT=Development



OTEL_DOTNET_AUTO_NETFX_REDIRECT_ENABLED=true OTEL_DOTNET_AUTO_LOG_DIRECTORY=/tmp/otel OTEL_LOG_LEVEL=debug OTEL_SERVICE_NAME=myapp OTEL_RESOURCE_ATTRIBUTES=deployment.environment=Development,service.version=1.0.0 ./Construction.WebApi



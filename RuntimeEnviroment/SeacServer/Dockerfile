#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/core/aspnet:3.1-buster-slim AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build
WORKDIR /src
COPY ["SeacServer/SeacServer.csproj", "SeacServer/"]
COPY ["CommonCoreLibrary/CommonCoreLibrary.csproj", "CommonCoreLibrary/"]
RUN dotnet restore "SeacServer/SeacServer.csproj"
COPY . .
WORKDIR "/src/SeacServer"
RUN dotnet build "SeacServer.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "SeacServer.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
COPY wait /wait
RUN chmod +x /wait
COPY /cert /root/.dotnet/https
COPY /SeacRepoData /src/RuntimeEnviroment/SeacRepoData
ENTRYPOINT /wait && dotnet SeacServer.dll

#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/core/aspnet:3.1-buster-slim AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build
WORKDIR /src
COPY ["OcelotAPI/OcelotAPI.csproj", "OcelotAPI/"]
COPY ["CommonCoreLibrary/CommonCoreLibrary.csproj", "CommonCoreLibrary/"]
RUN dotnet restore "OcelotAPI/OcelotAPI.csproj"
COPY . .
WORKDIR "/src/OcelotAPI"
RUN dotnet build "OcelotAPI.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "OcelotAPI.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
COPY wait /wait
RUN chmod +x /wait
COPY /cert /root/.dotnet/https
ENTRYPOINT /wait && dotnet OcelotAPI.dll
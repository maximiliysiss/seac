using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace SeacServer.Migrations
{
    public partial class addRelease : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Developer",
                table: "Applications",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "ApplicationReleases",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    DateTime = table.Column<DateTime>(nullable: false),
                    Version = table.Column<string>(nullable: true),
                    ApplicationId = table.Column<int>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_ApplicationReleases", x => x.Id);
                    table.ForeignKey(
                        name: "FK_ApplicationReleases_Applications_ApplicationId",
                        column: x => x.ApplicationId,
                        principalTable: "Applications",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateIndex(
                name: "IX_ApplicationReleases_ApplicationId",
                table: "ApplicationReleases",
                column: "ApplicationId");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "ApplicationReleases");

            migrationBuilder.DropColumn(
                name: "Developer",
                table: "Applications");
        }
    }
}

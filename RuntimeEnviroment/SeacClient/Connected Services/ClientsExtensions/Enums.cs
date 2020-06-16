namespace SeacClient.Connected_Services.ClientsExtensions
{
    public enum ExecuteMode
    {
        Single,
        Remote,
        FullRemote
    }


    public static class EnumConverter
    {
        public static SeacClient.SeacRuntime.ExecuteMode Raw(this ExecuteMode executeMode) => (SeacClient.SeacRuntime.ExecuteMode)executeMode;
    }

}

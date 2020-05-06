using System;
using System.Windows;
using ToastNotifications;
using ToastNotifications.Lifetime;
using ToastNotifications.Messages;
using ToastNotifications.Position;

namespace SeacClient.Services
{
    public interface INotificationService
    {
        void NotifySuccess(string text);
        void NotifyError(string text);
    }

    public class NotificationService : INotificationService
    {
        private readonly Notifier notifier = new Notifier(cfg =>
        {
            cfg.PositionProvider = new WindowPositionProvider(
                parentWindow: Application.Current.MainWindow,
                corner: Corner.TopRight,
                offsetX: 10,
                offsetY: 10);

            cfg.LifetimeSupervisor = new TimeAndCountBasedLifetimeSupervisor(
                notificationLifetime: TimeSpan.FromSeconds(3),
                maximumNotificationCount: MaximumNotificationCount.FromCount(5));

            cfg.Dispatcher = Application.Current.Dispatcher;
        });

        public void NotifyError(string text)
        {
            notifier.ShowError(text);
        }

        public void NotifySuccess(string text)
        {
            notifier.ShowSuccess(text);
        }
    }
}

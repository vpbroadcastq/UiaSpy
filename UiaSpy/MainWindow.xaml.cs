using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Windows.Foundation;
using Windows.Foundation.Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace UiaSpy
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public ObservableCollection<Models.UiaTreeEntry> UiaTreeEntries { get; private set; }

        public MainWindow()
        {
            this.InitializeComponent();
            PopulateTree();
        }

        private void myButton_Click(object sender, RoutedEventArgs e)
        {
            myButton.Content = "Clicked";
        }
        private void PopulateTree()
        {
            UiaTreeEntries = new ObservableCollection<Models.UiaTreeEntry>
            {
                new Models.UiaTreeEntry("Root")
                {
                    Children =
                    {
                        new Models.UiaTreeEntry("Folder 1")
                        {
                            Children =
                            {
                                new Models.UiaTreeEntry("File 1.1"),
                                new Models.UiaTreeEntry("File 1.2")
                            }
                        },
                        new Models.UiaTreeEntry("Folder 2")
                        {
                            Children =
                            {
                                new Models.UiaTreeEntry("File 2.1"),
                                new Models.UiaTreeEntry("File 2.2")
                            }
                        }
                    }
                }
            };
            /*// Create root node
            TreeViewNode rootNode = new TreeViewNode() { Content = "Root Folder", IsExpanded = true };

            // Create first child node
            TreeViewNode childNode1 = new TreeViewNode() { Content = "Folder 1" };
            childNode1.Children.Add(new TreeViewNode() { Content = "File 1.1" });
            childNode1.Children.Add(new TreeViewNode() { Content = "File 1.2" });

            // Create second child node
            TreeViewNode childNode2 = new TreeViewNode() { Content = "Folder 2" };
            childNode2.Children.Add(new TreeViewNode() { Content = "File 2.1" });
            childNode2.Children.Add(new TreeViewNode() { Content = "File 2.2" });

            // Add children to root node
            rootNode.Children.Add(childNode1);
            rootNode.Children.Add(childNode2);

            // Set the root node to TreeView
            MyTreeView.RootNodes.Add(rootNode);*/
        }
    }
}

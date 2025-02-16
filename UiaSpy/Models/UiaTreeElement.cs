using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace UiaSpy.Models
{
    public class UiaTreeEntry
    {
        public string Name { get; set; }
        public ObservableCollection<UiaTreeEntry> Children {get; set;}

        public UiaTreeEntry(string name)
        {
            Name = name;
            Children = new ObservableCollection<UiaTreeEntry>();
        }
    }
}



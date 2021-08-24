using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.VisualStudio.Shell;

namespace NewWorldVisualStudioExtension
{
    class GetItemFolder
    {
        [Flags]
        public enum SelectionTypes
        {
            Other = 0,
            Solution = 1,
            Folder = 2
        }

        public static SelectionTypes GetItemType(object item)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            EnvDTE.UIHierarchyItem currentItem = item as EnvDTE.UIHierarchyItem;
            
            if (currentItem == null)
            {
                return SelectionTypes.Other;
            }

            if (currentItem.Object as EnvDTE.Solution != null)
            {
                return SelectionTypes.Solution;
            }

            if (currentItem.Collection.Parent as EnvDTE.UIHierarchyItem != null)
            {
                return SelectionTypes.Folder;
            }

            return SelectionTypes.Other;
        }

        public static string GetPath(object item)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            string path = "";

            EnvDTE.UIHierarchyItem currentItem = item as EnvDTE.UIHierarchyItem;

            if (currentItem != null)
            {
                path = currentItem.Name;

                currentItem = currentItem.Collection.Parent as EnvDTE.UIHierarchyItem;

                while (currentItem != null)
                {
                    path = currentItem.Name + "\\" + path;
                    currentItem = currentItem.Collection.Parent as EnvDTE.UIHierarchyItem;
                }

                return path;
            }
            
            return null;
        }
    }
}

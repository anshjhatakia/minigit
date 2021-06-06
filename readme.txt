Welcome to Minigit!
Made by Ansh Jhatakia

Minigit is a mini version control system. It gives users the ability to make different versions of files, and 
easily return to past versions if desired. Minigit works with txt, cpp, and hpp files.

After Minigit initializes a repository, it presents the users with four options: Add File, Remove File, Commit, and Checkout.
________________________________________________________________________________________________________________________________
ADD FILE:
Add File allows users to select files that they would like to add to the current version of their projects. Once that 
file is committed , minigit will store the different versions of the files. Any changes made to the file will be resulted in a 
new version which minigit store and will be accessible in newer commits.

If this option is selected, Minigit will propmt the user to enter their file's name. If the file does not exist in the directory 
that Minigit runs out of, Minigit will allow the user to try entering the name again. This will continue until the user enters a 
valid file.
________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________
REMOVE FILE: 
If a user decides that they do not want a file that minigit is storing versions of, they can choose to remove the file. Removing
file means that future versions of the file will not be saved by Minigit. However, if the user were to go back to a commit where
the file was tracked, they would still be able to access the file.

If this option is selected, Minigit will prompt the user to enter their file's name. If the file does not exist in the directory 
that Minigit runs out of, Minigit will allow the user to try entering the name again. This will continue until the user enters a 
valid file. 
______________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________
COMMIT:
Once a user is finished making the changes they want to their project, they can commit the changes. This essentially makes a 
new "version" of thier project. The version has an associated commit number, which will be shown in the program's version list.

If this option is selected, the commit will be made and the user will be led back to the main menu.
________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________
CHECKOUT:
Checkout allows individuals to visit and view files from past versions of the program. To do so, they must know the commit number
of the version they want to go back to. If individuals make changes to files and commit before using Checkout, they will lose all 
of their local progress. Users will not be able to use the Add File, Remove File, or Commit features while checking out another
version. If they want to make changes, they must re-select checkout and return back to the latest version, where all of the
features will be unlocked.

If this option is selected, users will be prompted to enter a number. They then need to read the warning message about loss of
changes and type "CONTINUE" into the program so that the checkout will commence.

________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________
GENERAL NOTES:
- Users will see a list of files that they have added if they choose to add a new file or remove another file. This is to simply
help the user not forget what they have left in their version. These versions will be committed when the user chooses to commit.
- After each commit, a list of all of the commits will be displayed on the screen. This is mainly to help the user decide which
version they want to return to. Commit numbers are also displayed for convenience.

I hope you enjoy my implementation of Minigit!
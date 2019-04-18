Project Teamwork Methodology
============================
After reading this chapter you should be able to collaborate with the project team, realize changes to the source
code, test them and create a new release.

## System Users
These are the main system users:  
• **Software Engineer**: It is the developer that creates the system and the continuous integration environ-
ment  
• **Pipeline Developer**: It is the user who develops new analysis pipelines combining the existing available
calculations  
• **Calculation Developer**: It is the software developer that uses the system to create new calculations  
• **End User**: It is the user who analyzes his/her data using already available pipelines  
• **Web Developer**: It is the developer that creates and maintains the project website  

## Vincent Driessen’s branching model
Follow the following steps for modifying the any file of the project:  
Please refer Figure 11.1 for Vincent Driessen’s branching model.  
• Download the project files to your computer:  
```bash
$ git clone https://github.com/CRAGENOMICA/ngasp.git
```  
• Your current branch is the master. Change to the develop one:  
```bash
$ git checkout develop
```  
• If you had already the develop branch in your computer for some time, be sure that it has not modified
by another developer in that time. Run a pull action for getting remote changes if they exist:  
```bash
$ git pull
```  
• You will create your own branch. For example, feature-calc-gccontent:  
```bash
$ git branch feature-calc-gccontent  
$ git checkout feature-calc-gccontent
$ git push --set-upstream origin feature-calc-gccontent
```  
• Now, you can modify the project files for adding the new feature. And when you finish it, add your
changes to your local repository:  
```bash
$ git add . --all  
$ git commit -am "I added a new calculation to the project called GCContent."
```  
• Your feature is not finished yet but you want to upload all your changes to the remote repository (for
backup purposes, ...). Run:  
```bash
$ # git pull <---- Before a push run always a pull if you share this branch with another  
developer. Maybe his/her changes break your code... So, if it happens maybe you don’t  
want to upload your code, yet.  
$ git push # <-- Upload your code to the remote repository
```  
• You finished. It is time to upload your files to the remote repository. Do it in the same way as described
before:  
```bash
$ git pull  
$ git push
```
• Now, you can merge your branch with the develop branch. Do:  
```bash
$ git checkout develop  # switch to the develop branch  
$ git merge feature-calc-gccontent  # do the merge
```  
• Once, it is decided that the develop branch can be a release, you can merge the develop branch with the
master branch:  
```bash
$ git checkout master  # switch to the master branch  
$ git merge develop  # do the merge
```  
• If Git shows conflicts that can no be resolved automatically. Do:  
```bash
$ sudo yum install meld  # install meld  
$ git config --global merge.tool meld  # Tell git that this is your merge tool  
$ git mergetool  # Resolve conflicts manually  
$ git add .  # Confirm  
$ git commit -am "Conflicts resolved manually."
```  
## Pull Request  
This project is intended to be stored into the GitHutb repository. Once it is there, external contributor
developers will be able to create a Fork of this project, update it and ask for a pull request to the project’s
owner.  
See [Pull Request] for further information about Pull Requests.  
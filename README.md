# Ft_ls

#### Purpose

The subject for this project is a bit self-explanatory:

I was required to re-code one of the most useful commands: ls.

In order to do that, I had to learn file systems inside and out and how files and directories are sorted.  

The allowed functions for this project are:
```
write
opendir
readdir
closedir
stat
lstat
getpwuid
getgrgid
listxattr
getxattr
time
ctime
readlink
malloc
free
perror
strerror
exit0
```

Most of these were used to retrive file information.

The required flags for this project are:
```
-lRart
```
However, I implemented some additional flags as a bonus as well:
```
-ufgd
```
And created some new ones too (sort by filename length and directories first
```
-yz
```

For this project, I used my Libft Library as well as my newly finished ft_printf function.


#### Usage

Clone the repository.  There is a makefile, so you only need to type `make` to create the executable.  It can them be used in the following way:
```
ft_ls [-Radfglrtuyz] [file ...]
```

#### What's so special about your version of ls?

I took the opportunity in this project to learn a new data structure that I had not used before, the AVL tree.  The AVL tree is a self-balancing binary search tree, which sped up my insertion and sorting for this project.  Thanks to [Rob Edwards](https://www.youtube.com/watch?v=-9sHvAnLN_w) for some very helpful videos!

I then used a pointer to function to apply my printing function on the tree, making it so I had to write much less code.  I learned a lot about trees in this project.

Want to know more about this project?

Feel free to read the included PDF instructions or reach out and ask a question!

![Grade](https://user-images.githubusercontent.com/29003743/62587773-45507d80-b878-11e9-8562-191ac9b3cb9c.png)
![level](https://user-images.githubusercontent.com/29003743/62587774-471a4100-b878-11e9-93e9-d18850263584.png)

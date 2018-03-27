*** Test 21sh  ***
=
*********************

Command simple
--

* ls
* ls -a
* ls -a -l

Builtins
-

env:

+ env
+ env ls
+ env -i ./21sh
+ env -i yo=mdr TERM=xterm-256color env
+ env -i yo=mdr wesh=mamie TERM=xterm-256color bash
+ env -i TERM=xterm-256color ./21sh

setenv:

+ setenv
+ setenv yo
+ setenv yo mdr
+ setenv yo=mdr
+ setenv yo = mdr
+ setenv yo=
+ setenv yo=mdr here
+ setenv yo=mdr here yo
+ setenv yo` mdr

unsetenv:

+ unsetenv PAGER
+ unsetenv PAGER HOME
+ unsetenv p`ager
+ unsetenv fsdfsdfsdfsdf

cd:

+ cd
+ cd /
+ cd /tmp
+ cd fdshglidfkhg
+ cd ~
+ **_unsetenv_HOME_cd_~**
+ unsetenv HOME **cd**
+ unsetenv OLDPWD **cd -**

echo:

+ echo
+ echo lol
+ echo lol mdr
+ echo -n lol
**a rajouter**


Quote
-

- ''
- 'ls'
- 'ls -a'
- "

"
- echo "today is the day"
- "''"
- """"""
- '

\'


Redirection
-

input

- cat < file

heredoc

- cat << EOF

output

- ls > file
- ls dfsffd 2> file
- ls 2> file

double redirection

- ls >> file

Space
-

- ls      -a
- ls;ls
- ls >file


Chained cmd
-

- ls ;
- ls ; ls ;
- cd ; ls ; setenv yo mdr ; env ; echo lol


Pipe
-

- ls | grep 21sh
- cat /dev/random | head -c 1000
- ls | grep Makefile | cat -e | head -c 10000
- ls | grep Makefile | sdfsdfdsf | head -c 10000



file aggregator
-

- \>&
- 1>&
- 1>&1
- 1>&2
- 2>&
- 1>&1
<br/> <br/>
- ls \>&
- ls 1>&
- ls 1>&1
- ls 1>&2
- ls 2>&
- ls 1>&1
<br/> <br/>
- ls fsd \>&
- ls sdfdsf \>&
- ls dsf 1>&1
- ls sdfd 1>&2
- ls sfdsf 2>&
- ls sdfdsf 1>&1
<br/> <br/>

- \<&
- 1<&
- 1<&1
- 1<&2
- 2<&
- 1<&1
<br/> <br/>
- ls \<&
- ls 1<&
- ls 1<&1
- ls 1<&2
- ls 2<&
- ls 1<&1
<br/> <br/>
- ls dasd \<&
- ls asdasd1 <&
- ls sdadas 1<&1
- ls dsadas 1<&2
- ls dsadas 2<&
- ls dsadas 1<&1

Conclusion Test
-

- mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
- cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd -; echo "I prefer turnips anyway" >> /tmp/better_poem; cat /tmp/better_poem" 
- cat -e << EOF >> /tmp/test.txt
- base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'
- env | grep "' fdsfdsfd .    " 2> file ; cat -e file | grep file | cat -e > file ; ls >> file ; ls dasdsa 2>&- ; echo 'Finish for today' ;
- env |
cat -e >> file | cat -e << EOF >> file ;

Fail Test
-

- \&
- \>
- \<
- \<<<
- \>>>

Other Test
-

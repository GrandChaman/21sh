# Test 21sh

*********************

## CLI

### - Easy

- Write text
- to the end of the line
- then delete all
- then write it again
- then use left arrow to go back to beginning
- then use right arrow to go back to end
- use shift+arrow to back and forth
- HOME
- END
- Alt+UP and Alt+DOWN

### - Selection

- Select text with Alt-LEFT
- Press another key
- Select text with Alt-RIGHT
- Press another key
- Select text and cut it with Alt-X
- Paste it 5 times with Alt-V
- Copy text with Alt-C
- Past it 5 times
- Copy nothing
- Try to paste
- Cut nothing
- Try to paste
- Try to cut from position 0
- Try to cut from last pos
- Try to cut from between lines
- Try to cut from last position

### - Autocomplete

- Press tab
- Press a key
- Press a

## Commands

### - Easy

* ls
* ls -a
* ls -a -l

### - Builtins
#### -- cd

+ cd /tmp
+ cd
+ cd -
+ cd ewfewf
+ cd -
+ cd ~
+ cd ~/Downloads
+ cd /~/ewf
+ unsetenv HOME ; cd ~
+ unsetenv HOME ; cd ~/Downloads
+ unsetenv HOME ; cd
+ unsetenv OLDPWD ; cd -
+ setenv OLDPWD=TOTO ; cd -
+ cd Makefile
+ mkdir toto ; chmod 000 toto ; cd toto

#### -- env:

+ env
+ env ls
+ env -i bash
+ env -i yo=mdr TERM=xterm-256color env
+ env -i yo=mdr TERM=xterm-256color
+ env -i yo=mdr wesh=mamie TERM=xterm-256color bash
+ env -i TERM=xterm-256color ./21sh
+ env ewf wef wef ls
+ env TOTO COUCOU ls
+ env TOTO=COUCOU bash

#### -- setenv:

+ setenv
+ setenv yo
+ setenv yo mdr
+ setenv yo=mdr
+ setenv yo = mdr
+ setenv yo=
+ setenv yo=mdr here
+ setenv yo=mdr here yo
+ setenv yo\` mdr
+ setenv 123wefewf mdr

#### -- unsetenv:

+ unsetenv
+ unsetenv PAGER
+ unsetenv PAGER HOME
+ unsetenv p\`ager
+ unsetenv fsdfsdfsdfsdf

#### -- hash:

- hash
- hash ewfwef
- unsetenv PATH ; hash
- setenv PATH=/usr/bin:/bin ; hash


### - Quote

- ''
- 'ls'
- 'ls -a'
- "

	"
- "''"
- """"""
- '

	'

### - echo:

+ echo
+ echo lol
+ echo lol mdr
+ echo -n lol
+ echo "Salut" "Comment" "Ca\n\n\n\n\n" "va"
+ echo "Salut \n\tva ?"

### - Redirection

-- TODO --

### - Input

- cat < Makefile
- cat < nonexistent
- cat -e < Makefile
- ls < Makefile

### - heredoc

- cat << EOF
- cat -e << EOF
- ls << EOF

### - output

- ls > file
- ls >
- ls 2>
- ls 3>
- ls p>
- ls dfsffd 2> file
- ls 2> file

### - double redirection

- ls >> file
- ls >> nonexistent
- ls >>

### - Space

- ls   			   -a
- ls;ls
- ls >file


### - Chained cmd

- ls ;
- ls ; ls ;
- cd ; ls ; setenv yo mdr ; env ; echo lol


### - Pipe

- ls | grep 21sh
- cat /dev/random | head -c 1000
- cat /dev/random | head -c 1000 | cat -e
- ls | grep Makefile | cat -e | head -c 10000
- ls | grep Makefile | sdfsdfdsf | head -c 10000

### - File aggregator

- \>&
- 1>&
- 1>&1
- 1>&2
- 2>&
- 1>&1


- ls \>&
- ls 1>&
- ls 1>&1
- ls 1>&2
- ls 2>&
- ls 1>&1


- ls fsd \>&
- ls sdfdsf \>&
- ls dsf 1>&1
- ls sdfd 1>&2
- ls sfdsf 2>&
- ls sdfdsf 1>&1


- \<&
- 1<&
- 1<&1
- 1<&2
- 2<&
- 1<&1


- ls \<&
- ls 1<&
- ls 1<&1
- ls 1<&2
- ls 2<&
- ls 1<&1


- ls dasd \<&
- ls asdasd1 <&
- ls sdadas 1<&1
- ls dsadas 1<&2
- ls dsadas 2<&
- ls dsadas 1<&1

### - Conclusion Test


- mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
- cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd -; echo "I prefer turnips anyway" >> /tmp/better_poem; cat /tmp/better_poem"
- cat -e << EOF >> /tmp/test.txt
- base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'
- env | grep "' fdsfdsfd .    " 2> file ; cat -e file | grep file | cat -e > file ; ls >> file ; ls dasdsa 2>&- ; echo 'Finish for today' ;
- env |
cat -e >> file | cat -e << EOF >> file ;

### - Fail Test

- \&
- \>
- \<
- \<<<
- \>>>

### - Grouped test (multi command + multi redirection)

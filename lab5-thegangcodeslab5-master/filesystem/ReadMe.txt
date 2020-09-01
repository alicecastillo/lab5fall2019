Group: Alice Castillo, Will Parkinson
Repo: thegangcodeslab5


We collaborated by discussing implementations and design patterns beforehand and demo-ing/explaining our implementations to each other.
Will did the LS, RM, CAT, and DS commands. Alice did the CP and SYM commands, extra credit (read only files), debugging, and this ReadMe.

Design choice: We used a Link Counter class to keep track of a dynamically allocated link count instead of the link count being contained within the proxy's variables because we had originally intended on expanding link counts and linking among proxies as part of our extra 
credit. We adapted LinkCount, once we settled on a DIFFERENT extra credit direction, so that it's all protected except for its friends--which are the proxies--in order to keep it more secure. The object is deleted upon the final proxy deletion just like
the proxy's referenced file in order to avoid memory leaks. 


LAB:

LSCommand:

TESTS:
-	NO OPTION: This checked to make sure the metadata would only display if the -l option was given
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	whale.txt
	dir1
	shark.img


-	***ERROR DETECTED*** MALFORMED INPUT: This checked to make sure that an invalid command couldn't accomplish what the correct one could.
	We ran into an error here because our command only checked input to see if it contained "-l" on the end, and didn't consider any text
	after that.
		ERROR EXAMPLES:
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls -llllll
		whale.txt
		dir1
		shark.img

		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls -l l
		whale.txt
		dir1
		shark.img

		***FIX*** What we were missing was an "else if" that checked to see if the length of options was greater than 2, which means that--because the if
		statement checked if it was "-l" in the beginning--it caught when the prompt was malformed. It printed out a statement notifying the user and returns
		invalidcommandprompt, indicating the command failed. 

		SUCCESSFUL TEST:
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls
		whale.txt
		weFixed
		it.txt

		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls -l
		-l
		whale.txt       text     size: 0
		weFixed directory        size: 0
		it.txt  text     size: 0
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls -lll
		Invalid command prompt
		command failed


-	CHECKED DISPLAY AT ROOT:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls -l
	whale.txt       text     size: 60
	dir1    directory        size: 0
	shark.img       image    size: 4
	

-	CHECKED DISPLAY AT DIRECTORIES (EMPTY AND NON-EMPTY); CHECKED UPDATED INFO:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EMPTY DIRECTORY DISPLAYS NOTHING
	root/dir1 $ ls -l
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ touch squid.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DIRECTORY UPDATED, NOW CONTAINS TXT FILE
	root/dir1 $ ls -l
	squid.txt       text     size: 0


*****************************

RM Command:

TESTS:
-	MALFORMED PROMPT:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch eel.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm eel.txt -rrrr																					<- INVALID COMMAND
	Invalid command prompt [See: Usage]
	command failed
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm eel.txt -r 																					<- VALID COMMAND
	deleting:eel.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls


-	REQUESTING DELETION OF NONEXISTENT FILE:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch blue.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- INVALID FILE NAME
	root $ rm humpback.img
	File does not exist
	command failed
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	blue.img


-	REMOVING A .TXT FILE:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch skate.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	dir1
	skate.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm skate.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	dir1


-	REMOVING A .IMG FILE:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch stingray.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	stingray.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm stingray.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls


-	REMOVING AN EMPTY DIRECTORY:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch emptydir
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	emptydir

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm emptydir
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls


-	REMOVING A FULL DIRECTORY: 
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ touch whale.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ rm dir1
	rm:root/dir1: is a directory that is not empty
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- RECURSIVE REMOVAL OF DIRECTORY'S FILES
	root $ rm dir1 -r
	deleting:whale.img
	deleting:dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls


*****************************

CAT Command & DS command:

TESTS:
-	MALFORMED INPUT:
	root $ touch whale.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat whale.img -aaaa
	Invalid command prompt
	command failed


-	INVALID FILE:
	root/dir1 $ cat joker.txt
	failed to open directory
	command failed


-	INVALID FORMAT FOR WRITE TO .IMG:
	root $ cat bird.img
	root/bird.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XXXXX2
	:wq
	invalid format, could not write to file


-	WRITE TO .IMG:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat blue.img
	root/blue.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XXXX2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DS FOR IMAGE
	root $ ds blue.img
	XX
	XX

	
-	***ERROR ENCOUNTERED*** While it doesn't, in the end, allow the user to cat -a onto an image file, it still gives the user
	the option when it never should in the first place. 

	-	ERROR EXAMPLES:
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ds blue.img
		XX
		XX


		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ cat blue.img -a
		root/blue.img
		Enter data you would like to write to the file.
		Enter:wq to save the file and exit, enter : q to exit without saving
		XX
		XX

		XXXXXXXXX3
		:wq
		invalid format, could not write to file

		***FIX*** The issue was that the args[filetype] was retrieving a string with both the file name AND the flag (e.g., in the case above, "blue.img -a").
		We fixed by changing the parameters of the substring to grab a substring from options bound by the "." and the space right after.

	-	SUCCESSFUL TRIALS:
		root $ touch whale.img
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ cat whale.img
		tyupe.img>
		namewhale.img>
		flag>
		root/whale.img
		Enter data you would like to write to the file.
		Enter:wq to save the file and exit, enter : q to exit without saving
		XXXX2
		:wq
		saved
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ cat whale.img -a
		fuckkkk.img
		Invalid argument: whale.img is an image
		Cannot append to an image, -a is not a valid flag for this type
		command failed


-	WRITING TO A .TXT & WRITING OVER THAT :
	root $ cat batman.txt
	root/batman.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	Batman isn't a real superhero
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat batman.txt
	root/batman.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	But he has hella money to buy powers
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DS FOR .TXT
	root $ ds batman.txt
	But he has hella money to buy powers

-	WRITING TO A .TXT AND APPENDING: (continuing with batman.txt from above):
	root $ cat batman.txt -a
	root/batman.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	But he has hella money to buy powers

	He also has many sidekicks
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds batman.txt
	But he has hella money to buy powers
	He also has many sidekicks


*****************************


DS Command (also ran tests with it above):

TESTS:

-	FORMATTED & RAW DATA:
	root/dir1 $ cat well.img
	root/dir1/well.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	X  X2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <-FORMATTED DS
	root/dir1 $ ds well.img
	 X
	X


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DATA ONLY DS
	root/dir1 $ ds well.img -d
	X  X


-	INVALID FILE:
	root/dir1 $ ds notwell.img
	failed to open file
	command failed

-	***ERROR ENCOUNTERED*** Similar command prompt error as ones described above; fix is the same. 
	-	ERROR EXAMPLE: 
		root/dir1 $ ds well.img -dddd
		 X
		X

		***FIX*** check size of option -d
	-	SUCCESSFUL TRIAL:
		root $ ds whale.txt -ddddd
		Invalid prompt
		command failed


*****************************


CP Command:

TESTS:

-	TESTING .TXT FILE:

	H:\332FL19\lab5-thegangcodeslab5\filesystem\x64\Debug>filesystem.exe
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch og.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat og.txt
	root/og.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	Original file to be copied
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds og.txt
	Original file to be copied


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY FILE FROM ROOT TO DIR1
	root $ cp og.txt root/dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- FILE APPEARS IN DIR1
	root/dir1 $ ls
	og.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING COPIED FILE
	root/dir1 $ cat og.txt
	root/dir1/og.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	this WON'T edit the original
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ds og.txt
	this WON'T edit the original


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPIED FILE CAT DIDN'T ALTER ORIGINAL
	root $ ds og.txt
	Original file to be copied


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DELETE ORIGINAL
	root $ rm og.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	dir1

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY STILL EXISTS IN DIR1
	root/dir1 $ ls
	og.txt


-	COPYING .IMG FILES:
	H:\332FL19\lab5-thegangcodeslab5\filesystem\x64\Debug>filesystem.exe
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch whale.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat whale.img
	root/whale.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XXXX2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds whale.img
	XX
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- TEST; HANDLES INVALID PATH CORRECTLY
	root $ cp whale.img dir1
	No valid path given
	command failed
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY ORIGINAL INTO DIR1
	root $ cp whale.img root/dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ls
	whale.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ds whale.img
	XX
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDIT COPIED FILE
	root/dir1 $ cat whale.img
	root/dir1/whale.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	X X 2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ds whale.img
	X
	X


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPIED FILE EDIT DIDN'T EDIT ORIGINAL
	root $ ds whale.img
	XX
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DELETING COPY
	root/dir1 $ rm whale.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ls

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- ORIGINAL STILL EXISTS; NOT AFFECTED BY COPY DELETION
	root $ ls
	whale.img
	dir1


-	COPYING DIRECTORY (you can't):
	H:\332FL19\lab5-thegangcodeslab5\filesystem\x64\Debug>filesystem.exe
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir2
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	dir1
	dir2

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- TRY TO CLONE DIRECTORY
	root $ cp dir1 root/dir2
	Cannot clone directories																				<- HANDLES INVALID INPUT


-	COPYING FILE INTO SAME DIRECTORY AS ORIGINAL:
	H:\332FL19\lab5-thegangcodeslab5\filesystem\x64\Debug>filesystem.exe
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch superman.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cp superman.txt root
	Invalid destination
	command failed


-	INVALID FILE NAME (DOESN'T EXIST): 
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	superman.txt
	dir1

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cp supergirl.txt root/dir1
	Invalid file
	command failed


-	INVALID PATH:
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cp superman.txt root/dir2
	Invalid destination
	command failed


*****************************


SYM Command:

TESTS:

	GENERAL FUNCTIONAL TEST:
	root $ ls
	dir1
	dir2
	dir3
	text.txt
	image.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- SYM LINK .txt INTO DIR1
	root $ sym text.txt root/dir1
	Link made to root/dir1/text.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- SYM LINK .img INTO DIR2
	root $ sym image.img root/dir2
	Link made to root/dir2/image.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXIES REMAIN IN ROOT
	root $ ls
	dir1
	dir2
	dir3
	text.txt
	image.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY TXT IS IN DIR1
	root/dir1 $ ls
	text.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir2
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY IMG IS IN DIR2
	root/dir2 $ ls
	image.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir2 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDIT ONE PROXY
	root $ cat text.txt
	root/text.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	This will be shown in ALL the proxies
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ls
	text.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING ONE PROXY EDITS ALL PROXIES 
	root/dir1 $ ds text.txt
	This will be shown in ALL the proxies


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY TO NEW DIR3
	root/dir1 $ sym text.txt root/dir3
	Link made to root/dir3/text.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir3
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING ONE PROXY EDITS ALL PROXIES
	root/dir3 $ ds text.txt
	This will be shown in ALL the proxies


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- REMOVING ONE PROXY ONLY REMOVES THAT ONE
	root/dir3 $ rm text.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir3 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- OTHER PROXIES REMAIN
	root $ ls
	dir1
	dir2
	dir3
	text.txt
	image.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- OTHER PROXIES REMAIN
	root/dir1 $ ls
	text.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING ONE PROXY IMG
	root $ cat image.img
	root/image.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	X  X2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds image.img
	 X
	X


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir2
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING ONE PROXY IMG EDITS ALL
	root/dir2 $ ds image.img
	 X
	X


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir2 $ sym image.img root
	Link made to root/image.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPYING PROXY RESULTS IN COPY OF FILE not THE PROXY ITESLF
	root/dir2 $ cp image.img root/dir3
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir2 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir3
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir3 $ cat image.img
	root/dir3/image.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XXXX2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING COPY 
	root/dir3 $ ds image.img
	XX
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir3 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITS MADE IN COPY DON'T AFFECT PROXIES
	root $ ds image.img
	 X
	X


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CANNOT PROXY DIRECTORY
	root $ sym dir1 root/dir2
	Directory File cannot be copied or proxied
	command failed


	PROXY VISIBILITY:

		> TREATED LIKE FILE IT POINTS TO: 
			To quit: q, For a list of commands: help, For information about a specific command: help <command name>
			root $ cat image.img -a
			Invalid argument: image.img is an image
			Cannot append to an image, -a is not a valid flag for this type
			command failed

		> LS -L DISPLAYS IT AS FILE IT POINTS TO: 
		To quit: q, For a list of commands: help, For information about a specific command: help <command name>
		root $ ls -l
		-l
		dir1    directory        size: 9
		dir2    directory        size: 10
		dir3    directory        size: 10
		text.txt        text     size: 38
		image.img       image    size: 4


	DELETING FINAL PROXY: 
	root $ touch i.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch t.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch dir2
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY MADE; 2 REFS TO FILE
	root $ sym i.img root/dir1
	Link made to root/dir1/i.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY DELETED; 1 REF LEFT TO FILE
	root $ rm i.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ ls
	i.img

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- ONLY DELETES FILE AND LINK COUNT WHEN FINAL PROXY IS DELETED
	root/dir1 $ rm i.img
	Final reference deleted. Image file deleted.
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY MADE; 2 REFS TO FILE
	root $ sym t.txt root/dir1
	Link made to root/dir1/t.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY MADE; 3 REFS TO FILE
	root $ sym t.txt root/dir2
	Link made to root/dir2/t.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY DELETED; 2 REFS TO FILE
	root/dir1 $ rm t.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir2
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- PROXY DELETED; 1 REF LEFT TO FILE
	root/dir2 $ rm t.txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir2 $ ls

	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir2 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	dir1
	dir2
	t.txt

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- ONLY DELETES FILE AND LINK COUNT WHEN FINAL PROXY IS DELETED
	root $ rm t.txt
	Final reference deleted. Text file deleted.




------------------------------------------------------------------------------------------------------------------------------------------------------
EXTRA CREDIT:

As described in our email to Professor Shidal, we implemented a read-only function for files that prohibits users from writing to it. 
However, like many wordprocessor docs, when you copy that read-only file you get a file that you CAN edit. We used proxies to enforce permissions
in this way without setting permissions directly in the AbstractFile class (e.g. ImageFile or TextFile). We amended TouchCommand to accept and then
use the optional command -ro in order to set this read-only permission. Read-only permission is only possible for images and text files. 


TRIALS:

-	CORRECT FORMAT, EXECUTION FOR .txt AND .img FILES:

	root $ touch editable.txt																				<- CREATE EDITABLE (NON READ ONL)Y .txt
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CREATE READ ONLY .txt
	root $ touch noedits.txt -ro
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CREATE EDITABLE (NON READ ONLY) .img
	root $ touch changeable.img
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CREATE READ ONLY .img
	root $ touch nochanges.img -ro
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> 
	root $ touch dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CANNOT CREATE READ ONLY DIRECTORY
	root $ touch dir2 -ro
	Cannot make directories read only
	command failed
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cat editable.txt
	root/editable.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	I can edit this one because I have permission to do so!
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds editable.txt
	I can edit this one because I have permission to do so!


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CANNOT EDIT READ ONLY .txt
	root $ cat noedits.txt
	root/noedits.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	It won't actually write this to the file
	:wq
	Permission denied. File <noedits.txt> is a READ-ONLY file.
	invalid format, could not write to file
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DOESN'T WRITE CHANGES TO FILE
	root $ ds noedits.txt


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPYING A READ ONLY GIVES YOU AN EDITABLE FILE
	root $ cp noedits.txt root/dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CAN EDIT COPY
	root/dir1 $ cat noedits.txt
	root/dir1/noedits.txt
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	I will be able to edit this because it is a copy!
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- SAVES CHANGES TO COPY
	root/dir1 $ ds noedits.txt
	I will be able to edit this because it is a copy!


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY INDEPENDENT OF READ ONLY
	root $ ds noedits.txt


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DELETION REVEALS READ ONLY AS PROXY 
	root $ rm noedits.txt
	Final reference deleted. Text file <noedits.txt> deleted.
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ls
	editable.txt
	changeable.img
	nochanges.img
	dir1

	To quit: q, For a list of commands: help, For information about a specific command: help <command name> 
	root $ cat changeable.img
	root/changeable.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XXXX2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CAN'T EDIT READ ONLY .img
	root $ cat nochanges.img
	root/nochanges.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	X X 2
	:wq
	Permission denied. File <nochanges.img> is a READ-ONLY file.
	invalid format, could not write to file
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ ds changeable.img
	XX
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- EDITING NOT SAVED (NOT WRITTEN)
	root $ ds nochanges.img


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY OF READ ONLY GIVES EDITABLE FILE
	root $ cp nochanges.img root/dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- CAN WRITE TO COPY
	root/dir1 $ cat nochanges.img
	root/dir1/nochanges.img
	Enter data you would like to write to the file.
	Enter:wq to save the file and exit, enter : q to exit without saving
	XX X2
	:wq
	saved
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- SAVES EDITS TO COPY
	root/dir1 $ ds nochanges.img
	 X
	XX


	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root/dir1 $ cd ..
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPY INDEPENDENT OF READ ONLY; CANNOT WRITE TO READ ONLY THRU COPY
	root $ ds nochanges.img


	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- DELETION REVEALS .img READ ONLY AS PROXY
	root $ rm nochanges.img
	Final reference deleted. Image file <nochanges.img> deleted.
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ cd dir1
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <- COPIES ARE NOT PROXIES BUT INSTEAD FILES
	root/dir1 $ rm nochanges.img																				|
	To quit: q, For a list of commands: help, For information about a specific command: help <command name> <----
	root/dir1 $ rm noedits.txt

	 
	BAD COMMAND ARGS/PROMPT:

	root $ touch badinput.t -ro				<- CHECKS IF VALID FILE TYPE											
	failed to create file
	command failed
	To quit: q, For a list of commands: help, For information about a specific command: help <command name>
	root $ touch badpromopt.txt -roooo		<- CHECKS IF VALID ARGS GIVEN
	Invalid command given
	command failed


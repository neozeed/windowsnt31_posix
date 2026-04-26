:
# NAME:
#	ksh.kshrc - global initialization for ksh 
#
# DESCRIPTION:
#	Each invocation of /bin/ksh processes the file pointed
#	to by $ENV (usually $HOME/.kshrc).
#	This file is intended as a global .kshrc file for the
#	Korn shell.  A user's $HOME/.kshrc file simply requires
#	the line:
#		. /etc/ksh.kshrc
#	at or near the start to pick up the defaults in this
#	file which can then be overridden as desired.
#
# SEE ALSO:
#	$HOME/.kshrc
#
# AMENDED:
#	91/11/12 19:39:44 (sjg)
#
# RELEASED:
#	91/11/12 19:39:46 v2.4
#
# SCCSID:
#	@(#)ksh.kshrc 2.4 91/11/12 19:39:44 (sjg)
#
#	@(#)Copyright (c) 1991 Simon J. Gerraty
#
#	This file is provided in the hope that it will
#	be of use.  There is absolutely NO WARRANTY.
#	Permission to copy, redistribute or otherwise
#	use this file is hereby granted provided that 
#	the above copyright notice and this notice are
#	left intact. 

case "$-" in
*i*)	# we are interactive
	# we may have su'ed so reset these
	# NOTE: SCO-UNIX doesn't have whoami,
	#	install whoami.sh
	USER=`whoami`
	PROMPT="<$USER@$HOSTNAME:!>$ "
	PPROMPT='<$USER@$HOSTNAME:$PWD:!>$ '
	PS1=$PPROMPT
	# $TTY is the tty we logged in on,
	# $tty is that which we are in now (might by pty)
	tty=`tty`
	tty=`basename $tty`

	set -o $EDITOR

	alias ls='ls -CF'
	alias h='fc -l | more'
	# the PD ksh is not 100% compatible
	case "$KSH_VERSION" in
	*PD*)	# PD ksh
		builtin=builtin
	        bind ^?=delete-char-backward
        	bind ^[^?=delete-word-backward
		;;
	*)	# real ksh ?
		builtin=""
		;;
	esac
	case "$TERM" in
	sun*)
		# these are not as neat as their csh equivalents
		if [ "$tty" != console ]; then
			ilabel () { print -n "\033]L$*\033\\"; }
			label () { print -n "\033]l$*\033\\"; }
			alias stripe='label $USER @ $HOSTNAME \($tty\) - $PWD'
			cds () { "cd" $*; eval stripe; }
			alias cd=cds
			eval stripe
			eval ilabel "$USER@$HOSTNAME"
			PS1=$PROMPT
		fi
		;;
	xterm*)
		# these are not as neat as their csh equivalents
		ilabel () { print -n "\033]1;$*\007"; }
		label () { print -n "\033]2;$*\007"; }
		alias stripe='label xterm: $USER @ $HOSTNAME \($tty\) - $PWD'
		cds () { "cd" $*; eval stripe; }
		alias cd=cds
		eval stripe
		eval ilabel "$USER@$HOSTNAME"
		PS1=$PROMPT
		;;
	*)	;;
	esac
	alias quit=exit
	alias cls=clear
	alias logout=exit
	alias bye=exit


# add your favourite aliases here
;;
*)	# non-interactive
;;
esac
# commands for both interactive and non-interactive shells

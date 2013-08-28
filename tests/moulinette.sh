#!/bin/sh
## moulinette.sh for find in /u/a1/moular_t/rendu/moular_t-find/tests
##
## Made by thomas moulard
## Login   <moular_t@epita.fr>
##
## Started on  Mon Oct  3 09:38:45 2005 thomas moulard
## Last update Sun Oct 23 05:31:19 2005 thomas moulard
##

r=`uname -s`

n_echec=0
for l in `ls *.in`; do
    test=`echo "$l" | sed 's/\.in$//'`

    echo '------------------------------'
    echo "* Test '$test'"

    echo '1/ Verification'
    if [ -r "$test.in" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier d'entree introuvable."
	exit 1
    fi
    if [ -r "$test.out" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier de sortie introuvable."
	exit 1
    fi
    if [ -r "$test.ret" ]; then
	echo -n ""
    else
	echo "ERREUR: fichier de retour introuvable."
	exit 1
    fi

    echo "2/ Execution"
    ../norps -f "$test.in" > "/tmp/$test.dump"

    result=`echo "$?"`

    cmp "$test.out" "/tmp/$test.dump"
    if [ `echo "$?"` -eq 0 ]; then
	if [ "$result" = `cat "$test.ret"` ]; then
	    echo "TEST REUSSI"
	else
	    echo "ERREUR: echec du test (fichiers de retour differents)"
	    n_echec=$(($n_echec+1))
	fi
    else
	echo "ERREUR: echec du test (fichiers de sortie differents)"
	n_echec=$(($n_echec+1))
    fi
    rm -f "/tmp/$test.dump"
    rm -f "a.out"
done

echo ''
echo ''
echo '------------------------------'
echo ''
if [ "$n_echec" -eq 0 ]; then
    echo 'Tous les tests ont reussi.'
else
    echo "ECHEC: certains tests ont echoue : $n_echec erreur(s)."
fi
exit "$n_echec"
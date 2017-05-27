kadai01.c
    $ gcc -W -Wall kadai01.c xorshift.c -o jampbm && ./jampbm image1.pbm 0.1

kadai02.c
    $ gcc -W -Wall kadai02.c xorshift.c -o rmjam && ./rmjam noised_image1.pbm

diff.c
    $ gcc -W -Wall diff.c -o getdiff && ./getdiff noised_image1.pbm noise_reducted_noised_image1.pbm

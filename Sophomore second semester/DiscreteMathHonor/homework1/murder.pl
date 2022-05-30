man(george).
man(john).
man(robert).
woman(barbara).
woman(christine).
woman(yolanda).

person(X) :- man(X).
person(X) :- woman(X).

location(bathroom).
location(dining).
location(kitchen).
location(livingroom).
location(pantry).
location(study).
weapon(bag).
weapon(firearm).
weapon(gas).
weapon(knife).
weapon(poison).
weapon(rope).

rule(A, B, C, D, E, F) :-
    person(A), person(B), person(C),
    person(D), person(E), person(F),
    \+A=B, \+A=C, \+A=D, \+A=E, \+A=F,
    \+B=C, \+B=D, \+B=E, \+B=F,
    \+C=D, \+C=E, \+C=F,
    \+D=E, \+D=F,
    \+E=F.

murderer(X) :-
    rule(Inbathroom, Indining, Inkitchen, Inliving, Inpantry, Instudy),
    rule(Withbag, Withfirearm, Withgas, Withknife, Withpoison, Withrope),

    man(Inkitchen),
    \+Inkitchen=Withrope,
    \+Inkitchen=Withknife,
    \+Inkitchen=Withbag,
    \+Inkitchen=Withfirearm,

    woman(Inbathroom),
    woman(Instudy),
    \+christine=Inbathroom,
    \+christine=Instudy,
    \+barbara=Indining,
    \+barbara=Inkitchen,
    \+barbara=Inliving,
    \+barbara=Inpantry,
    \+yolanda=Indining,
    \+yolanda=Inkitchen,
    \+yolanda=Inliving,
    \+yolanda=Inpantry,

    \+barbara=Withbag,
    \+george=Withbag,
    \+Withbag=Inbathroom,
    \+Withbag=Indining,

    woman(Withrope),
    Withrope=Instudy,

    man(Inliving),
    \+Inliving=robert,

    \+Withknife=Indining,

    \+yolanda=Inpantry,
    \+yolanda=Instudy,

    Withfirearm=george,

    Inpantry=Withgas,
    Inpantry=X,
    Withgas=X.

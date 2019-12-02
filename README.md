# PETGYN_Study

System to generate images, pdfs and Dynamic C libraries based on matematical equations.

It uses a lexial and sintatical analyser to manipulate and/or find errors in the inserted equation.

All the generated files by defalut will have the same as the "Fname" (check bellow). So to run the executable, use ./'Fname' and insert the variable values in the order they were inserted (you can use the Pdf or the Png to check).

Examples can be found in "BaseEquations" folder.

There is a old Bison and Flex implementation that is outdated in "otherImplementations" folder.

## Function model

    Fname (variable1,variable2,variable3) = expression

##  Dependencies

Magic Touch with Pdf->Png conversion enabled.
flex and bison libraries installed (only for compiling).


## Compiling

Utilize the make command.

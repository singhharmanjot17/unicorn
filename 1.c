.text 
.globl main
main:
addi $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addi $sp, $sp, -52
li $t1, 1
sw $t1, 36($sp)
li $t1, 2
sw $t1, 32($sp)
li $t1, 3
sw $t1, 28($sp)
li $t1, 6
sw $t1, 24($sp)
lw $t2, 36($sp)
nop 
sw $t2, 20($sp)
lw $t2, 32($sp)
nop 
sw $t2, 16($sp)
lw $t2, 20($sp)
nop 
lw $t3, 16($sp)
nop 
add $t1, $t2, $t3
sw $t1, 12($sp)
lw $t2, 28($sp)
nop 
sw $t2, 8($sp)
lw $t2, 12($sp)
nop 
lw $t3, 8($sp)
nop 
add $t1, $t2, $t3
sw $t1, 4($sp)
lw $t2, 24($sp)
nop 
sw $t2, 0($sp)
lw $t2, 4($sp)
nop 
lw $t3, 0($sp)
nop 
sub $t0, $t2, $t3
move $v0, $t0
lw $fp, 56($sp)
nop 
lw $ra, 52($sp)
nop 
addi $sp, $sp, 60
jr $ra
nop 
addi $sp, $sp, 52
lw $fp, 4($sp)
nop 
lw $ra, 0($sp)
nop 
addi $sp, $sp, 8
jr $ra
nop 
addi $sp, $sp, 8
 

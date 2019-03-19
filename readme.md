HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [ ] **If you volunteer to give the presentation next week, check this.**

--------------------

## 1. 實驗題目  
更改main.c，並且透過組合語言及QEMU觀察C語言函式呼叫之情形

## 2. 實驗步驟

* 改寫main.c檔
```
int addten(int a)
{
        int b=a+10;
        return b;
}

int test5parameter(int a,int b,int c,int d,int e)
{
        return (a*1)+(b*2)+(c*3)+(d*4)+(e*5);
}


void reset_handler(void)
{
        int x=addten(5);
        int y=test5parameter(1,2,3,4,5);
        while (1)
                ;
}
```
* 利用makefile進行編譯的動作，得到如下:  
```
Disassembly of section .mytext:

00000000 <addten-0x8>:
   0:	20000100 	andcs	r0, r0, r0, lsl #2
   4:	00000061 	andeq	r0, r0, r1, rrx

00000008 <addten>:
   8:	b480      	push	{r7}
   a:	b085      	sub	sp, #20
   c:	af00      	add	r7, sp, #0
   e:	6078      	str	r0, [r7, #4]
  10:	687b      	ldr	r3, [r7, #4]
  12:	330a      	adds	r3, #10
  14:	60fb      	str	r3, [r7, #12]
  16:	68fb      	ldr	r3, [r7, #12]
  18:	4618      	mov	r0, r3
  1a:	3714      	adds	r7, #20
  1c:	46bd      	mov	sp, r7
  1e:	f85d 7b04 	ldr.w	r7, [sp], #4
  22:	4770      	bx	lr

00000024 <test5parameter>:
  24:	b480      	push	{r7}
  26:	b085      	sub	sp, #20
  28:	af00      	add	r7, sp, #0
  2a:	60f8      	str	r0, [r7, #12]
  2c:	60b9      	str	r1, [r7, #8]
  2e:	607a      	str	r2, [r7, #4]
  30:	603b      	str	r3, [r7, #0]
  32:	68bb      	ldr	r3, [r7, #8]
  34:	005a      	lsls	r2, r3, #1
  36:	68fb      	ldr	r3, [r7, #12]
  38:	18d1      	adds	r1, r2, r3
  3a:	687a      	ldr	r2, [r7, #4]
  3c:	4613      	mov	r3, r2
  3e:	005b      	lsls	r3, r3, #1
  40:	4413      	add	r3, r2
  42:	18ca      	adds	r2, r1, r3
  44:	683b      	ldr	r3, [r7, #0]
  46:	009b      	lsls	r3, r3, #2
  48:	18d1      	adds	r1, r2, r3
  4a:	69ba      	ldr	r2, [r7, #24]
  4c:	4613      	mov	r3, r2
  4e:	009b      	lsls	r3, r3, #2
  50:	4413      	add	r3, r2
  52:	440b      	add	r3, r1
  54:	4618      	mov	r0, r3
  56:	3714      	adds	r7, #20
  58:	46bd      	mov	sp, r7
  5a:	f85d 7b04 	ldr.w	r7, [sp], #4
  5e:	4770      	bx	lr

00000060 <reset_handler>:
  60:	b580      	push	{r7, lr}
  62:	b084      	sub	sp, #16
  64:	af02      	add	r7, sp, #8
  66:	2005      	movs	r0, #5
  68:	f7ff ffce 	bl	8 <addten>
  6c:	6078      	str	r0, [r7, #4]
  6e:	2305      	movs	r3, #5
  70:	9300      	str	r3, [sp, #0]
  72:	2001      	movs	r0, #1
  74:	2102      	movs	r1, #2
  76:	2203      	movs	r2, #3
  78:	2304      	movs	r3, #4
  7a:	f7ff ffd3 	bl	24 <test5parameter>
  7e:	6038      	str	r0, [r7, #0]
  80:	e7fe      	b.n	80 <reset_handler+0x20>
  82:	bf00      	nop

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <reset_handler+0x10d0cc4>
   4:	35312820 	ldrcc	r2, [r1, #-2080]!	; 0xfffff7e0
   8:	392e343a 	stmdbcc	lr!, {r1, r3, r4, r5, sl, ip, sp}
   c:	732b332e 			; <UNDEFINED> instruction: 0x732b332e
  10:	33326e76 	teqcc	r2, #1888	; 0x760
  14:	37373131 			; <UNDEFINED> instruction: 0x37373131
  18:	2029312d 	eorcs	r3, r9, sp, lsr #2
  1c:	2e392e34 	mrccs	14, 1, r2, cr9, cr4, {1}
  20:	30322033 	eorscc	r2, r2, r3, lsr r0
  24:	35303531 	ldrcc	r3, [r0, #-1329]!	; 0xfffffacf
  28:	28203932 	stmdacs	r0!, {r1, r4, r5, r8, fp, ip, sp}
  2c:	72657270 	rsbvc	r7, r5, #112, 4
  30:	61656c65 	cmnvs	r5, r5, ror #24
  34:	00296573 	eoreq	r6, r9, r3, ror r5

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00003041 	andeq	r3, r0, r1, asr #32
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000026 	andeq	r0, r0, r6, lsr #32
  10:	726f4305 	rsbvc	r4, pc, #335544320	; 0x14000000
  14:	2d786574 	cfldr64cs	mvdx6, [r8, #-464]!	; 0xfffffe30
  18:	0600344d 	streq	r3, [r0], -sp, asr #8
  1c:	094d070d 	stmdbeq	sp, {r0, r2, r3, r8, r9, sl}^
  20:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
  28:	1a011803 	bne	4603c <reset_handler+0x45fdc>
  2c:	22061e01 	andcs	r1, r6, #1, 28
  30:	Address 0x0000000000000030 is out of bounds.
```
* 先將資料夾 gnu-mcu-eclipse-qemu 完整複製到 ESEmbedded_HW03 資料夾中  
* 利用qemu觀察暫存器之情形
* 讀Cortex-M4的指令集，讓我們更了解底層運作  



## 3. 結果與討論
* 透過這次的作業，得知要呼叫function時，會先將r7 push，然後將stack pointer空出來。  
  當主程式呼叫function時，會先利用r0,r1,r2,r3  
* 若不夠用時才會用到stack，要傳遞參數時才會將參數load出來到暫存器，做完運算後在load到r    
  直到最後將結果用r0回傳


res_gen:
        .zero   4
res_wm:
        .zero   4
res_dw:
        .zero   4
int_gen:
        .zero   4
int_wm:
        .zero   4
int_dw:
        .zero   4
count:
        .zero   4
stato:
        .zero   4
main:
        mov     eax, DWORD PTR stato      # stato.0_1, stato
        test    eax, eax        # stato.0_1
        jne     .L2       #,
        mov     eax, DWORD PTR res_gen    # res_gen.1_2, res_gen
        test    eax, eax        # res_gen.1_2
        je      .L2 #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_gen, 1      # int_gen,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 1       # int_dw,
.L2:
        mov     eax, DWORD PTR stato      # stato.2_3, stato
        cmp     eax, 1    # stato.2_3,
        jne     .L3       #,
        mov     eax, DWORD PTR count      # count.3_4, count
        cmp     eax, 4    # count.3_4,
        jne     .L3       #,
        mov     DWORD PTR stato, 2        # stato,
        mov     DWORD PTR int_dw, 0       # int_dw,
.L3:
        mov     eax, DWORD PTR stato      # stato.4_5, stato
        cmp     eax, 2    # stato.4_5,
        jne     .L4       #,
        mov     eax, DWORD PTR count      # count.5_6, count
        test    eax, eax        # count.5_6
        je      .L5 #,
        mov     DWORD PTR int_wm, 0       # int_wm,
        mov     eax, DWORD PTR res_dw     # res_dw.6_7, res_dw
        test    eax, eax        # res_dw.6_7
        je      .L6 #,
        mov     DWORD PTR stato, 8        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L4       #
.L6:
        mov     DWORD PTR stato, 3        # stato,
        jmp     .L4       #
.L5:
        mov     eax, DWORD PTR res_dw     # res_dw.7_8, res_dw
        test    eax, eax        # res_dw.7_8
        je      .L8 #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L4       #
.L8:
        mov     eax, DWORD PTR res_dw     # res_dw.8_9, res_dw
        test    eax, eax        # res_dw.8_9
        jne     .L4       #,
        mov     DWORD PTR stato, 4        # stato,
.L4:
        mov     eax, DWORD PTR stato      # stato.9_10, stato
        cmp     eax, 3    # stato.9_10,
        jne     .L9       #,
        mov     eax, DWORD PTR count      # count.10_11, count
        test    eax, eax        # count.10_11
        je      .L10        #,
        mov     DWORD PTR stato, 0        # stato,
        mov     DWORD PTR int_gen, 0      # int_gen,
        jmp     .L9       #
.L10:
        mov     eax, DWORD PTR res_dw     # res_dw.11_12, res_dw
        test    eax, eax        # res_dw.11_12
        je      .L11        #,
        mov     eax, DWORD PTR res_wm     # res_wm.12_13, res_wm
        test    eax, eax        # res_wm.12_13
        jne     .L11      #,
        mov     DWORD PTR stato, 5        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L9       #
.L11:
        mov     eax, DWORD PTR res_wm     # res_wm.13_14, res_wm
        test    eax, eax        # res_wm.13_14
        je      .L12        #,
        mov     eax, DWORD PTR res_dw     # res_dw.14_15, res_dw
        test    eax, eax        # res_dw.14_15
        jne     .L12      #,
        mov     DWORD PTR stato, 4        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L9       #
.L12:
        mov     eax, DWORD PTR res_wm     # res_wm.15_16, res_wm
        test    eax, eax        # res_wm.15_16
        je      .L13        #,
        mov     eax, DWORD PTR res_dw     # res_dw.16_17, res_dw
        test    eax, eax        # res_dw.16_17
        je      .L13        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L9       #
.L13:
        mov     DWORD PTR stato, 6        # stato,
.L9:
        mov     eax, DWORD PTR stato      # stato.17_18, stato
        cmp     eax, 4    # stato.17_18,
        jne     .L14      #,
        mov     eax, DWORD PTR count      # count.18_19, count
        test    eax, eax        # count.18_19
        je      .L15        #,
        mov     DWORD PTR stato, 7        # stato,
        mov     eax, DWORD PTR res_dw     # res_dw.19_20, res_dw
        test    eax, eax        # res_dw.19_20
        je      .L14        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L14      #
.L15:
        mov     eax, DWORD PTR res_dw     # res_dw.20_21, res_dw
        test    eax, eax        # res_dw.20_21
        je      .L14        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
.L14:
        mov     eax, DWORD PTR stato      # stato.21_22, stato
        cmp     eax, 5    # stato.21_22,
        jne     .L17      #,
        mov     eax, DWORD PTR count      # count.22_23, count
        test    eax, eax        # count.22_23
        je      .L18        #,
        mov     DWORD PTR stato, 8        # stato,
        mov     eax, DWORD PTR res_wm     # res_wm.23_24, res_wm
        test    eax, eax        # res_wm.23_24
        je      .L17        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L17      #
.L18:
        mov     eax, DWORD PTR res_wm     # res_wm.24_25, res_wm
        test    eax, eax        # res_wm.24_25
        je      .L17        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
.L17:
        mov     eax, DWORD PTR stato      # stato.25_26, stato
        cmp     eax, 6    # stato.25_26,
        jne     .L20      #,
        mov     eax, DWORD PTR count      # count.26_27, count
        test    eax, eax        # count.26_27
        je      .L21        #,
        mov     eax, DWORD PTR res_dw     # res_dw.27_28, res_dw
        test    eax, eax        # res_dw.27_28
        je      .L22        #,
        mov     DWORD PTR stato, 7        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L20      #
.L22:
        mov     eax, DWORD PTR res_wm     # res_wm.28_29, res_wm
        test    eax, eax        # res_wm.28_29
        je      .L24        #,
        mov     DWORD PTR stato, 8        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L20      #
.L24:
        mov     edx, DWORD PTR res_dw     # res_dw.29_30, res_dw
        mov     eax, DWORD PTR res_wm     # res_wm.30_31, res_wm
        and     eax, edx  # _32, res_dw.29_30
        test    eax, eax        # _32
        je      .L25        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L20      #
.L25:
        mov     DWORD PTR stato, 9        # stato,
        jmp     .L20      #
.L21:
        mov     edx, DWORD PTR res_dw     # res_dw.31_33, res_dw
        mov     eax, DWORD PTR res_wm     # res_wm.32_34, res_wm
        and     eax, edx  # _35, res_dw.31_33
        test    eax, eax        # _35
        je      .L26        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L20      #
.L26:
        mov     eax, DWORD PTR res_wm     # res_wm.33_36, res_wm
        test    eax, eax        # res_wm.33_36
        je      .L27        #,
        mov     DWORD PTR stato, 4        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L20      #
.L27:
        mov     eax, DWORD PTR res_dw     # res_dw.34_37, res_dw
        test    eax, eax        # res_dw.34_37
        je      .L20        #,
        mov     DWORD PTR stato, 5        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
.L20:
        mov     eax, DWORD PTR stato      # stato.35_38, stato
        cmp     eax, 7    # stato.35_38,
        jne     .L28      #,
        mov     eax, DWORD PTR count      # count.36_39, count
        test    eax, eax        # count.36_39
        je      .L29        #,
        mov     eax, DWORD PTR res_dw     # res_dw.37_40, res_dw
        test    eax, eax        # res_dw.37_40
        je      .L30        #,
        mov     eax, DWORD PTR count      # count.38_41, count
        cmp     eax, 3    # count.38_41,
        jg      .L30        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L28      #
.L30:
        mov     eax, DWORD PTR res_dw     # res_dw.39_42, res_dw
        test    eax, eax        # res_dw.39_42
        je      .L32        #,
        mov     eax, DWORD PTR count      # count.40_43, count
        cmp     eax, 4    # count.40_43,
        jne     .L32      #,
        mov     DWORD PTR stato, 2        # stato,
        jmp     .L28      #
.L32:
        mov     eax, DWORD PTR res_dw     # res_dw.41_44, res_dw
        test    eax, eax        # res_dw.41_44
        je      .L33        #,
        mov     eax, DWORD PTR count      # count.42_45, count
        cmp     eax, 5    # count.42_45,
        jne     .L33      #,
        mov     DWORD PTR stato, 2        # stato,
        jmp     .L28      #
.L33:
        mov     eax, DWORD PTR count      # count.43_46, count
        cmp     eax, 5    # count.43_46,
        jne     .L28      #,
        mov     DWORD PTR stato, 9        # stato,
        mov     DWORD PTR int_wm, 0       # int_wm,
        jmp     .L28      #
.L29:
        mov     eax, DWORD PTR res_dw     # res_dw.44_47, res_dw
        test    eax, eax        # res_dw.44_47
        je      .L34        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L28      #
.L34:
        mov     DWORD PTR stato, 4        # stato,
.L28:
        mov     eax, DWORD PTR stato      # stato.45_48, stato
        cmp     eax, 8    # stato.45_48,
        jne     .L35      #,
        mov     eax, DWORD PTR count      # count.46_49, count
        test    eax, eax        # count.46_49
        je      .L36        #,
        mov     eax, DWORD PTR count      # count.47_50, count
        cmp     eax, 5    # count.47_50,
        jne     .L37      #,
        mov     DWORD PTR stato, 3        # stato,
        jmp     .L35      #
.L37:
        mov     eax, DWORD PTR count      # count.48_51, count
        cmp     eax, 6    # count.48_51,
        jne     .L39      #,
        mov     DWORD PTR stato, 0        # stato,
        mov     DWORD PTR int_gen, 0      # int_gen,
        mov     DWORD PTR int_dw, 0       # int_dw,
        jmp     .L35      #
.L39:
        mov     eax, DWORD PTR res_wm     # res_wm.49_52, res_wm
        test    eax, eax        # res_wm.49_52
        je      .L40        #,
        mov     eax, DWORD PTR count      # count.50_53, count
        cmp     eax, 3    # count.50_53,
        jg      .L40        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L35      #
.L40:
        mov     eax, DWORD PTR res_wm     # res_wm.51_54, res_wm
        test    eax, eax        # res_wm.51_54
        je      .L35        #,
        mov     eax, DWORD PTR count      # count.52_55, count
        cmp     eax, 4    # count.52_55,
        jne     .L35      #,
        mov     DWORD PTR stato, 2        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 0       # int_dw,
        jmp     .L35      #
.L36:
        mov     eax, DWORD PTR res_wm     # res_wm.53_56, res_wm
        test    eax, eax        # res_wm.53_56
        je      .L41        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L35      #
.L41:
        mov     DWORD PTR stato, 5        # stato,
.L35:
        mov     eax, DWORD PTR stato      # stato.54_57, stato
        cmp     eax, 9    # stato.54_57,
        jne     .L42      #,
        mov     eax, DWORD PTR count      # count.55_58, count
        test    eax, eax        # count.55_58
        je      .L43        #,
        mov     eax, DWORD PTR count      # count.56_59, count
        cmp     eax, 6    # count.56_59,
        jne     .L44      #,
        mov     DWORD PTR stato, 0        # stato,
        mov     DWORD PTR int_gen, 0      # int_gen,
        mov     DWORD PTR int_dw, 0       # int_dw,
        jmp     .L42      #
.L44:
        mov     eax, DWORD PTR res_wm     # res_wm.57_60, res_wm
        test    eax, eax        # res_wm.57_60
        je      .L46        #,
        mov     eax, DWORD PTR count      # count.58_61, count
        cmp     eax, 5    # count.58_61,
        jg      .L46        #,
        mov     DWORD PTR stato, 7        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L42      #
.L46:
        mov     eax, DWORD PTR res_dw     # res_dw.59_62, res_dw
        test    eax, eax        # res_dw.59_62
        je      .L42        #,
        mov     DWORD PTR stato, 8        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L42      #
.L43:
        mov     eax, DWORD PTR res_wm     # res_wm.60_63, res_wm
        test    eax, eax        # res_wm.60_63
        je      .L47        #,
        mov     eax, DWORD PTR res_dw     # res_dw.61_64, res_dw
        test    eax, eax        # res_dw.61_64
        je      .L47        #,
        mov     DWORD PTR stato, 1        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L42      #
.L47:
        mov     eax, DWORD PTR res_wm     # res_wm.62_65, res_wm
        test    eax, eax        # res_wm.62_65
        je      .L48        #,
        mov     DWORD PTR stato, 4        # stato,
        mov     DWORD PTR int_wm, 1       # int_wm,
        jmp     .L42      #
.L48:
        mov     eax, DWORD PTR res_dw     # res_dw.63_66, res_dw
        test    eax, eax        # res_dw.63_66
        je      .L49        #,
        mov     DWORD PTR stato, 5        # stato,
        mov     DWORD PTR int_dw, 1       # int_dw,
        jmp     .L42      #
.L49:
        mov     DWORD PTR stato, 6        # stato,
.L42:
        mov     eax, 0    # _169,
        ret     
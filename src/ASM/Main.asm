;;
; This is NASM implementation of Swiss hash table. Open addressing and linear probing is used.
;  
;  Author: Chinthaka Senanayaka
;  Year: 2025
;;

; Program constants
SYS_EXIT  equ 1
SYS_WRITE equ 4
STDOUT    equ 1

; BSS variables section
section .bss

   ; Meta element structural definition for hash table to store position and hash value data
   struc MetadataElement
      .position: resd 1
      .hashValue: resd 1
   endstruc

   ; Hash table structural definition for hash table to store elements, meta data, 
   ; number of elements and hash table size data
   struc HashTable
      .numberOfElements: resd	1
      .hashTableSize: resd	1
      .elementArray: resq 1
      .metaArray: resq 1
   endstruc

   ; Variables to store data to refer when printing
   indexVal resd 1
   elementVal resd 1
   positionVal resd 1
   hashVal resd 1
   printTextLine resb 100

   ; Variables to store data to refer when printing insert
   insertVal resd 1
   insertPrintTextLine resb 100

   ; Variables to store data to refer when printing search result
   searchVal resd 1
   searchIdxVal resd 1
   searchPrintTextLine resb 100

   ; Variables to store data to refer when printing delete
   deleteVal resd 1
   deletePrintTextLine resb 100

   ; Variables to store heap memory size data of the application
   initialBreak resq 1
   currentBreak resq 1
   newBreak resq 1

   ; Variable to store error code for heap memory size extending and shrinking
   memError resd 1

   ; Variables to store hash table data when inserting data
   insertElmntVar resd 1
   directInsertElmntVar resd 1
   transferInsertElmntVar resd 1
   insertPosVar resd 1
   insertHashVar resd 1

   ; 0 if insert value, 1 if transfer value
   insertValPath resd 1

   ; Variables to store hash table data when deleting data
   deleteElmntVar resd 1
   deleteValPos resd 1
   crntDelHashIndex resd 1
   nxtDelHashIndex resd 1
   hashValueToDelete resd 1
   nxtDelHashVar resd 1

   ; Variables to store hash table data when searching data
   searchElmntVar resd 1
   searchPosVar resd 1
   searchHashVar resd 1

   ; temp variables
   tempHashTableSize resd 1
   tempResizeIndex resd 1

; Applocation constants section
section	.data

   ; Print message constants
   hashMsg db '==================Hash Table====================', 10, 0
   hashMsgLen equ $ - hashMsg

   ; Print hash table raw constants
   indexText db '[[index: ', 0
   indexTextLen equ $ - indexText
   elementText db ", element: ", 0
   elementTextLen equ $ - elementText
   positionText db "], [position: ", 0
   positionTextLen equ $ - positionText
   hashText db ", hashValue: ", 0
   hashTextLen equ $ - hashText
   endText db "]]", 10, 0
   endTextLen equ $ - endText

   ; Print insert element position constants
   insertValText db 'Inserting ', 0
   insertValTextLen equ $ - insertValText
   insertEndText db ': ', 10, 0
   insertEndTextLen equ $ - insertEndText

   ; Print search element position constants
   searchValText db 'Search for ', 0
   searchValTextLen equ $ - searchValText
   searchIdxText db " and found at index: ", 0
   searchIdxTextLen equ $ - searchIdxText
   searchEndText db 10, 0
   searchEndTextLen equ $ - searchEndText

   ; Print delete element position constants
   deleteValText db 'Deleting ', 0
   deleteValTextLen equ $ - deleteValText
   deleteEndText db ': ', 10, 0
   deleteEndTextLen equ $ - deleteEndText

   ; Print lengths for hash table fields constants
   printValLen dd 4
   printElementLen dd 100

   ; Print lengths for insert value constants
   insertPrintValLen dd 4
   insertPrintElementLen dd 100

   ; Print lengths for search value constants
   searchPrintValLen dd 4
   searchPrintElementLen dd 100

   ; Print lengths for delete value constants
   deletePrintValLen dd 4
   deletePrintElementLen dd 100

   ; Byte lengths of element and meta element memory sections
   ; Integers are allocated with 4 bytes (32 bits)
   metaElmntBytLen dd MetadataElement_size
   elmntBytLen dd 4

   ; Default values for hash table fields constants
   defaultElementVal dd -1
   defaultPositionVal dd -1
   defaultHashVal dd -1
   defaultElementArr dd -1, -1, -1, -1

   ; Hash table resizing constants
   resizingFactor dd 2

   ; Hash table load factor constants
   maxFactorVal dd 2                                ; 2 * numberOfElements > hashTableSize - inverse of Max Load Factor
   minFactorVal dd 4                                ; 4 * numberOfElements < hashTableSize - inverse of Min Load Factor

   ; SIMD variables
   sseBytLen dd 16
   sseDwordLen dd 4
   sseMetaElmntLen dd 2

   ; Hash table variable (object)
   hashtable:
      istruc HashTable
         at HashTable.numberOfElements, dd 0        ; number of elements in the hash table
         at HashTable.hashTableSize, dd 0           ; size of the hash table
         at HashTable.elementArray, dq 0            ; elements array starting memory address
         at HashTable.metaArray, dq 0               ; meta elements array starting memory address
      iend

; Application code section
section	.text
   global _start

; Application main start
_start:

   ; Set initial lowest heap address
   xor  rax, rax                    ; invalid 0 address to get initial break
   mov  [currentBreak], rax
   call malloc
   mov  [initialBreak], rax

   ; create the hash table object
   xor  rcx, rcx
   mov  rcx, 0                               ; number of elements
   call createHashTable

   ; print the initial hash table
   call printHashTable
   
   ; print inserting 57 message
   mov  rax, dword 57
   call printInsertElement

   ; insert 57
   mov  rax, dword 57
   call insertElement

   ; print the current hash table
   call printHashTable

   ; print inserting 18 message
   mov  rax, dword 18
   call printInsertElement

   ; insert 18
   mov  rax, dword 18
   call insertElement

   ; print the current hash table
   call printHashTable

   ; print inserting 105 message
   mov  rax, dword 105
   call printInsertElement

   ; insert 105
   mov  rax, dword 105
   call insertElement

   ; print the current hash table
   call printHashTable

   ; print inserting 109 message
   mov  rax, dword 109
   call printInsertElement

   ; insert 109
   mov  rax, dword 109
   call insertElement

   ; print the current hash table
   call printHashTable

   ; search 18 in the hash table
   mov  rax, dword 18
   call searchElement

   ; print 18 pisition in the hash table
   mov  rax, dword 18
   call printSearchElement

   ; search 105 in the hash table
   mov  rax, dword 105
   call searchElement

   ; print 105 pisition in the hash table
   mov  rax, dword 105
   call printSearchElement

   ; search 27 in the hash table
   mov  rax, dword 27
   call searchElement

   ; print 27 pisition in the hash table
   mov  rax, dword 27
   call printSearchElement

   ; print deleting 18 message
   mov  rax, dword 18
   call printDeleteElement

   ; delete 18
   mov  rax, dword 18
   call deleteElement

   ; print the current hash table
   call printHashTable

   ; print deleting 57 message
   mov  rax, dword 57
   call printDeleteElement

   ; delete 57
   mov  rax, dword 57
   call deleteElement

   ; print the current hash table
   call printHashTable

   ; finish the main program.
   call exit

; Create hash table procedure
; 
; Input:
;     rcx - number of elements to have in the hash table
; Output:
;     rax - hash table memory address
createHashTable:

   mov  [hashtable + HashTable.numberOfElements], ecx
   ; Get hash table size using number of elements
   call getHashTableSize
   mov  [hashtable + HashTable.hashTableSize], ecx

   mov  rax, [initialBreak]
   mov  [hashtable + HashTable.elementArray], rax

   xor  rax, rax                                      ; number of bytes to allocate
   call getElementArrayMemSize
   call malloc

   mov  rax, [currentBreak]
   mov  [hashtable + HashTable.metaArray], rax

   call getMetaArrayMemSize
   call malloc

   ; insert default values for all meta elements
   call insertDefaultValues

   ret

; Get full element array memory size
; 
; Input:
;     
; Output:
;     rax - element array memory size
getElementArrayMemSize:

   ; calculate element array memory size
   mov  eax, [elmntBytLen]
   mov  edx, [hashtable + HashTable.hashTableSize]
   mul  edx

   ret

; Get full meta element array memory size
; 
; Input:
;     
; Output:
;     rax - meta array memory size
getMetaArrayMemSize:

   ; calculate meta element memory size
   mov  eax, [metaElmntBytLen]
   mov  edx, [hashtable + HashTable.hashTableSize]
   mul  edx

   ret

; Get hash table size based on the current number of elements in the table
; 
; Input:
;     
; Output:
;     rcx - hash table size
getHashTableSize:

   xor  rcx, rcx
   mov  [tempHashTableSize], dword 1            ; min hash table size = 1

   mov  ebx, [maxFactorVal]

   calculateHashTableSize:

      mov  eax, [tempHashTableSize]
      mov  ecx, [resizingFactor]                ; hash table will be expanded or shrinked using this number
      mul  ecx
      xor  rdx, rdx
      mov  [tempHashTableSize], eax

      mov  eax, [hashtable + HashTable.numberOfElements]
      mul  ebx
      xor  rdx, rdx
      mov  ecx, [tempHashTableSize]
      cmp  eax, ecx
      jg  calculateHashTableSize

   mov  ecx, [tempHashTableSize]

   ret

; Insert default values (-1) for elements, meta elements
; Input:
;     hashtable - hash table
; Output:
;     
insertDefaultValues:

   xor  rcx, rcx
   mov  ecx, [hashtable + HashTable.hashTableSize]
   call insertDefaultValue

   ret

; Insert default value for 1 row in the hash table
; Input:
;     hashtable - hash table
; Output:
;     
insertDefaultValue:

   xor  rax, rax
   mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
   sub  rax, rcx

   push rax

   mov  rbx, [hashtable + HashTable.elementArray]
   mov  edx, [elmntBytLen]
   mul  rdx
   add  rbx, rax

   movss xmm0, [defaultElementVal]
   shufps  xmm0, xmm0, 0
   movups [rbx], xmm0

   pop  rax

   mov  rbx, [hashtable + HashTable.metaArray]
   mov  edx, [metaElmntBytLen]
   mul  rdx
   add  rbx, rax

   movss xmm0, [defaultElementVal]
   shufps  xmm0, xmm0, 0
   movups [rbx], xmm0

   xor  rdx, rdx
   mov  edx, [sseBytLen]
   add  rbx, rdx
   movups [rbx], xmm0

   ; loop by 16 bytes
   xor  rdx, rdx
   mov  edx, [sseDwordLen]

   sub  rcx, rdx
   cmp  rcx, 0
   jg   insertDefaultValue

   ret

; Insert element
; Input:
;     rax - element to be inserted
; Output:
;     
insertElement:

   mov  [directInsertElmntVar], rax

   ; calculate current load factor
   xor  rax, rax
   mov  eax, [hashtable + HashTable.numberOfElements]
   add  eax, 1                                           ; Add 1 element
   mov  [hashtable + HashTable.numberOfElements], eax
   mov  edx, [maxFactorVal]
   mul  edx

   ; check for hash table size resize
   mov  edx, [hashtable + HashTable.hashTableSize]
   cmp  edx, eax
   jge  useExisitngHashTable

   ; Resize before insert if max load factor is exceeded
   call resizeHashTable
   
   useExisitngHashTable:
      mov  rbx, 0
      mov  [insertValPath], rbx
      call insertToHashTable

   ret

; Insert to current existing hash table (no resizing)
; Input:
;     insertValPath - 0 if direct insert without resizing, 1 if transfer elements from old to new resized
;     directInsertElmntVar - element value if direct insert
;     transferInsertElmntVar - element value if transfer after table resizing
; Output:
;     hashtable - hash table
insertToHashTable:

   ; Check whether to direct insert if path is 0
   xor  rax, rax
   mov  eax, [insertValPath]
   cmp  eax, 0
   je  directInsert

   mov  eax, [transferInsertElmntVar]
   mov  [insertElmntVar], eax

   directInsert:

      ; Check whether to transfer element after resizing if path is 1
      xor  rax, rax
      mov  eax, [insertValPath]
      cmp  eax, 1
      je  transferInsert

      mov  eax, [directInsertElmntVar]
      mov  [insertElmntVar], eax

      transferInsert:
         
         xor  rbx, rbx
         mov  [insertHashVar], ebx                       ; clean up hash and pos vars
         mov  [insertPosVar], ebx

         mov  eax, [insertElmntVar]
         call getOpenAddrLinearProbHash                  ; calculate hash value
         mov  [insertHashVar], edx

         xor  rcx, rcx
         mov  ecx, [hashtable + HashTable.hashTableSize]
         call handleInsertCollisions                     ; handle insert collisions

   ret

; Hash table resizing
; Input:
;     hashtable - hash table
; Output:
;     hashtable - resized and with all the elements inserted
resizeHashTable:

   xor  rcx, rcx
   mov  rbp, rsp

   mov  ecx, [hashtable + HashTable.hashTableSize]

   ; Loads current hash tabl's all elements to the stack
   loadAllOldElements:

      xor  rax, rax
      mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
      sub  eax, ecx
      mov  [tempResizeIndex], eax

      ; retrieve meta element position to check value available
      xor  rbx, rbx
      mov  ebx, [metaElmntBytLen]
      mul  rbx
      mov  rbx, [hashtable + HashTable.metaArray]
      add  rbx, rax
      add  rbx, MetadataElement.position

      xor  rax, rax
      mov  eax, dword [rbx]                     ; meta position
      cmp  rax, 32768                           ; negative number check for default values to ignore
      jge  loadNxtPos
      
      mov  eax, [tempResizeIndex]

      ; retrieve element to push to stack
      xor  rbx, rbx
      mov  ebx, [elmntBytLen]
      mul  rbx
      mov  rbx, [hashtable + HashTable.elementArray]
      add  rbx, rax

      xor  rax, rax
      mov  eax, [rbx]                 ; element
      push rax                        ; push valid elements to the stack

      loadNxtPos:

      dec rcx
      jnz loadAllOldElements           ; repeat for all the values
   
   ; Create new resized hash table
   mov  ecx, [hashtable + HashTable.numberOfElements]       ; number of elements
   call createHashTable
   
   ; Insert elements to new hash table
   insertElementNewHashTable:

      pop  rax
      mov  [transferInsertElmntVar], rax
      mov  rax, 1
      mov  [insertValPath], rax
      call insertToHashTable                    ; insert transfer elements

      cmp  rbp, rsp
      jne  insertElementNewHashTable

   ret

; Handle insert collisions
; Input:
;     insertElmntVar - value to be inserted
; Output:
;     hash table - hash table with new element inserted
handleInsertCollisions:
   
   push rcx

   xor  rbx, rbx
   mov  [insertPosVar], ebx                        ; clean up position var

   xor  rax, rax
   mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
   sub  rax, rcx

   mov  rbx, rax
   xor  rax, rax
   mov  eax, [insertElmntVar]
   call getOpenAddrLinearProbHash
   mov  [insertPosVar], edx

   xor  rax, rax
   mov  eax, [metaElmntBytLen]
   mul  rdx

   ; inserting meta element
   mov  rbx, [hashtable + HashTable.metaArray]
   add  rbx, rax

   pxor  xmm0, xmm0
   movups  xmm0, [rbx]
   xor  rdx, rdx
   pextrd  edx, xmm0, 0                         ; check for collision

   cmp  rdx, 32768                              ; negative number check for insert
   jge  insertIn0thPos

   pextrd  edx, xmm0, 2
   cmp  rdx, 32768                              ; negative number check for insert
   jge  insertIn1stPos

   cmp  rdx, 32768                              ; negative number check for insert
   jl  insertInNxtPos

   ; inserting position value and hash value
   insertIn0thPos:
      xor  rax, rax
      xor  rdx, rdx
      mov  eax, [insertPosVar]
      mov  edx, [insertHashVar]

      pinsrd  xmm0, eax, 0
      pinsrd  xmm0, edx, 1
      movups  [rbx], xmm0
      jmp  insertRelevantElement

   insertIn1stPos:
      xor  rax, rax
      xor  rdx, rdx
      mov  eax, [insertPosVar]
      add  eax, 1                               ; add insertPosVar 1 as next position
      mov  edx, [insertHashVar]

      pinsrd  xmm0, eax, 2
      pinsrd  xmm0, edx, 3
      movups  [rbx], xmm0

   ; inserting 1 element
   insertRelevantElement:

      mov  rbx, [hashtable + HashTable.elementArray]
      xor  rdx, rdx
      mov  edx, [elmntBytLen]
      mul  rdx                                  ; rax is insertPosVar
      add  rbx, rax

      xor  rdx, rdx
      mov  edx, [insertElmntVar]
      mov  [rbx], edx

      pop  rcx
      ret

   insertInNxtPos:

   pop  rcx

   ; loop by 2 meta elements (2*2 position values and hash values - 16 bytes)
   xor  rdx, rdx
   mov  edx, [sseMetaElmntLen]

   sub  rcx, rdx
   cmp  rcx, 0
   jg   handleInsertCollisions

   ret

; Input:
;     rax - value
;     rbx - linear probe value
; Output:
;     rdx - hash value
getOpenAddrLinearProbHash:

   xor  rcx, rcx
   mov  ecx, [hashtable + HashTable.hashTableSize]
   xor  rdx, rdx
   div  rcx                                     ; idiv is not used to have positive hash values only
   add  rdx, rbx
   
   mov  rax, rdx
   xor  rdx, rdx
   div  rcx                                     ; rdx is hash value

   ret

; Input:
;     rax - memory size bytes to allocate
; Output:
;     rax - heap end memory address
malloc:

   mov  rbx, [currentBreak]
   add  rbx, rax

   mov  rax, 45                         ; system call brk
   int  0x80

   mov  [currentBreak], rax

   mov  rdx, rax
   add  rdx, '0'
   mov  [memError], rdx
   cmp  rax, 0
   jl	printMemError

   ret

; Search element in the hash table
; Input:
;     rax - element to be searched in the hash table
; Output:
;     rdx - element's position in the hash table (-1 if not found)
searchElement:

   mov  [searchElmntVar], rax

   xor  rbx, rbx
   mov  [searchHashVar], ebx                       ; clean up hash and pos vars
   
   call getOpenAddrLinearProbHash
   mov  [searchHashVar], edx

   xor  rcx, rcx
   mov  ecx, [hashtable + HashTable.hashTableSize]
   call handleSearchCollisions

   ret

; Handle search collisions
; Input:
;     searchElmntVar - element to be searched in the hash table
; Output:
;     rdx - element's position in the hash table (-1 if not found)
handleSearchCollisions:
   
   push rcx

   xor  rbx, rbx
   mov  [searchPosVar], ebx                        ; clean up position var

   xor  rax, rax
   mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
   sub  rax, rcx

   mov  rbx, rax
   xor  rax, rax
   mov  eax, [searchElmntVar]
   call getOpenAddrLinearProbHash                  ; rdx has position value

   xor  rax, rax
   mov  eax, [metaElmntBytLen]
   mul  rdx

   ; searching meta element
   mov  rbx, [hashtable + HashTable.metaArray]
   add  rbx, rax

   pxor  xmm0, xmm0
   movups  xmm0, [rbx]
   xor  rdx, rdx
   pextrd  edx, xmm0, 1                         ; check for collision

   cmp  rdx, 32768                              ; negative number check for default value
   jge  searchValNotFound

   ; if default value is not found, then it's a collision
   mov  eax, [searchHashVar]
   cmp  rdx, rax
   je  searchIn0thPos                           ; hash value is found

   pextrd  edx, xmm0, 3
   cmp  rdx, 32768                              ; negative number check for default value
   jge  searchValNotFound

   cmp  rdx, rax
   je   searchIn1stPos                           ; hash value is found

   cmp  rdx, 32768                               ; negative number check for default value
   jl   searchInNxtPos

   ; searching value element
   searchIn0thPos:

      xor  rdx, rdx
      pextrd  edx, xmm0, 0
      mov  [searchPosVar], edx

      mov  rbx, [hashtable + HashTable.elementArray]
      xor  rax, rax
      mov  eax, [elmntBytLen]
      mul  rdx
      add  rbx, rax

      xor  rax, rax
      xor  rcx, rcx
      mov  eax, [searchElmntVar]
      mov  ecx, [rbx]
      cmp  rax, rcx
      je   searchValFound

      jmp  searchInNxtPos                          ; After resolving collisions, value is not found
   
   searchIn1stPos:
      
      xor  rdx, rdx
      pextrd  edx, xmm0, 2
      add  rdx, 1
      mov  [searchPosVar], edx

      mov  rbx, [hashtable + HashTable.elementArray]
      xor  rax, rax
      mov  eax, [elmntBytLen]
      mul  rdx
      add  rbx, rax

      xor  rax, rax
      xor  rcx, rcx
      mov  eax, [searchElmntVar]
      mov  ecx, [rbx]
      cmp  rax, rcx
      je   searchValFound

   searchInNxtPos:                                 ; After resolving collisions, value is not found

   pop  rcx

   ; loop by 2 meta elements (2*2 position values and hash values - 16 bytes)
   xor  rdx, rdx
   mov  edx, [sseMetaElmntLen]

   sub  rcx, rdx
   cmp  rcx, 0
   jg   handleSearchCollisions

   ret
   
   searchValNotFound:
      mov  dx, [defaultPositionVal]
      movzx rdx, dx

      pop  rcx
      ret
   
   searchValFound:
      xor  rdx, rdx
      mov  edx, [searchPosVar]

      pop  rcx
      ret

; Delete element
; Input:
;     rax - value to delete
; Output:
;     rdx - delete status, 1 if deleted, if couldn't delete 0 otherwise -1
deleteElement:

   mov  [deleteElmntVar], rax

   call searchElement
   mov  [deleteValPos], edx
   mov  [crntDelHashIndex], edx

   cmp  rdx, 32768                              ; negative number check
   jge  deleteValNotFound        ; if default value is found then value is not found to delete

   xor  rax, rax
   xor  rbx, rbx
   mov  eax, [deleteElmntVar]
   call getOpenAddrLinearProbHash
   mov  [hashValueToDelete], edx          ; hash value of value to to be deleted

   ; Delete collision handling and cluster reorganizing
   xor  rcx, rcx
   mov  ecx, [hashtable + HashTable.hashTableSize]
   sub  rcx, 1

   ; Collision handling for deletion
   handleDeleteCollisions:

      push rcx

      xor  rax, rax
      mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index and index starts from 1
      sub  rax, rcx
      
      mov  rbx, rax
      xor  rax, rax
      mov  eax, [deleteElmntVar]
      call getOpenAddrLinearProbHash
      mov  [nxtDelHashIndex], edx         ; next position hash value

      mov  rbx, [hashtable + HashTable.metaArray]

      xor  rdx, rdx
      mov  edx, [metaElmntBytLen]
      xor  rax, rax
      mov  eax, [nxtDelHashIndex]
      mul  rdx
      add  rbx, rax

      pxor  xmm0, xmm0
      movups  xmm0, [rbx]
      xor  rcx, rcx
      pextrd  ecx, xmm0, 1                         ; next position's hash value
      
      cmp  rcx, 32768                              ; negative number check
      jge  deleteCurrentValue                      ; next value doesn't exist, check current element to delete

      xor  rbx, rbx
      mov  ebx, [hashValueToDelete]
      cmp  ecx, ebx
      jle  reposProbedVal

      pextrd  ecx, xmm0, 3

      cmp  rcx, 32768                              ; negative number check
      jge  deleteCurrentValue                      ; next value doesn't exist, check current element to delete

      cmp  ecx, ebx
      jg  checkNextDelPos

      ; add next del hash index 1 since xmm0 2nd half
      mov  eax, [nxtDelHashIndex]
      add  eax, 1
      mov  [nxtDelHashIndex], eax

      ; reposition previously linear probed values
      reposProbedVal:

         xor  rax, rax
         xor  rdx, rdx
         mov  edx, [elmntBytLen]

         mov  eax, [nxtDelHashIndex]

         mul  edx

         mov  rcx, [hashtable + HashTable.elementArray]
         add  rcx, rax

         xor  rbx, rbx
         mov  ebx, [rcx]

         xor  rax, rax
         xor  rdx, rdx
         mov  edx, [elmntBytLen]

         mov  eax, [crntDelHashIndex]
         mul  edx

         mov  rcx, [hashtable + HashTable.elementArray]
         add  rcx, rax

         mov  [rcx], ebx      ; assign next delete position element to current position element

         ; reposition meta elements
         xor  rax, rax
         xor  rdx, rdx
         mov  edx, [metaElmntBytLen]

         mov  eax, [nxtDelHashIndex]
         mul  edx

         ; sse can't be used for below since we may not be copying adjucent values
         mov  rcx, [hashtable + HashTable.metaArray]
         add  rcx, rax
         add  rcx, MetadataElement.hashValue

         xor  rbx, rbx
         mov  ebx, [rcx]                     ; next delete position hash value

         xor  rax, rax
         xor  rdx, rdx
         mov  edx, [metaElmntBytLen]

         mov  eax, [crntDelHashIndex]
         mul  edx

         mov  rcx, [hashtable + HashTable.metaArray]
         add  rcx, rax
         add  rcx, MetadataElement.hashValue

         mov  [rcx], ebx                  ; assign next delete position value to current position value

         xor  rax, rax
         mov  eax, [nxtDelHashIndex]
         mov  [crntDelHashIndex], eax

      checkNextDelPos:

      pop  rcx

      ; loop by 2 meta elements (2*2 position values and hash values - 16 bytes)
      xor  rdx, rdx
      mov  edx, [sseMetaElmntLen]

      sub  rcx, rdx
      cmp  rcx, 0
      jg   handleDeleteCollisions

      ret
   
   deleteCurrentValue:

      ; meta element is deleted with setting default meta values
      xor  rax, rax
      xor  rdx, rdx
      mov  edx, [metaElmntBytLen]

      mov  eax, [crntDelHashIndex]
      mul  edx

      mov  rcx, [hashtable + HashTable.metaArray]
      add  rcx, rax
      mov  rbx, rcx

      xor  rdx, rdx
      add  rcx, MetadataElement.position
      mov  edx, [defaultPositionVal]
      mov  [rcx], dword edx

      add  rbx, MetadataElement.hashValue
      mov  edx, [defaultHashVal]
      mov  [rbx], dword edx

      ; value is deleted with setting default value
      xor  rax, rax
      xor  rdx, rdx
      mov  edx, [elmntBytLen]

      mov  eax, [crntDelHashIndex]
      mul  edx

      mov  rcx, [hashtable + HashTable.elementArray]
      add  rcx, rax
      xor  rdx, rdx
      mov  edx, [defaultElementVal]
      mov  [rcx], dword edx

      ; check to shrink the hash table
      ; calculate current load factor
      xor  rax, rax
      mov  eax, [hashtable + HashTable.numberOfElements]
      sub  eax, 1                                           ; remove 1 element
      mov  [hashtable + HashTable.numberOfElements], eax
      mov  edx, [minFactorVal]
      mul  edx

      ; check for hash table size resize
      mov  edx, [hashtable + HashTable.hashTableSize]
      cmp  edx, eax
      jl   keepExistingHashTable

      ; shrink the hash table
      call resizeHashTable

      keepExistingHashTable:

      pop  rcx

      ; set return 1
      xor  rdx, rdx
      mov  edx, 1

      ret

   deleteValNotFound:

      ; set return -1
      xor  rdx, rdx
      mov  edx, [defaultPositionVal]

      ret

; Print memory allocation error if error happened when expanding/shrinking memory
; Input:
;     memError - memory error code
; Output:
;     
printMemError:

   mov  rax, 2
   mov  rbx, memError
   call print

   call exit

   ret

; Pretty print the entire hash table
; Input:
;     hashtable - hash table to print
; Output:
;     
printHashTable:

   ; print hash table start
   mov  rax, hashMsgLen
   mov  rbx, hashMsg
   call print

   ; print hash table row by row
   xor  rcx, rcx
   mov  ecx, [hashtable + HashTable.hashTableSize]
   call printHashTableElement

   ; print hash table end
   mov  rax, hashMsgLen
   mov  rbx, hashMsg
   call print

   ret

; Pretty print hash table row by row
; Input:
;     hashtable - hash table to print
; Output:
;    
printHashTableElement:

   ; clean print variable before storing new values
   xor  rax, rax
   mov  [elementVal], rax
   mov  [positionVal], rax
   mov  [hashVal], rax

   mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
   sub  rax, rcx

   push rcx
   push rax

   ; print row index
   mov  rbx, indexVal
   call convertDigitsToText                     ; converts integers to text to print
   
   pop  rax

   xor  rdx, rdx
   mov  edx, [elmntBytLen]
   mul  rdx                                           ; index is in rax & loop counter is in rcx

   mov  rcx, indexTextLen
   mov  rsi, indexText
   mov  rbx, printTextLine
   mov  rdi, rbx
   cld
   rep  movsb
   mov  ecx, [printValLen]
   mov  rsi, indexVal
   add  rbx, indexTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; print row element
   mov  rcx, elementTextLen
   mov  rsi, elementText
   mov  edx, [printValLen]
   add  rbx, rdx
   mov  rdi, rbx
   cld
   rep  movsb

   mov  rdx, [hashtable + HashTable.elementArray]
   add  rdx, rax

   push rbx
   mov  ax, [rdx]
   movzx rax, ax
   mov  rbx, elementVal
   call convertDigitsToText                     ; converts integers to text to print
   pop  rbx

   mov  ecx, [printValLen]
   mov  rsi, elementVal
   add  rbx, elementTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; print row meta element position
   pop rcx

   mov  eax, [hashtable + HashTable.hashTableSize] ; calculate index
   sub  rax, rcx

   mov  edx, [metaElmntBytLen]
   mul  rdx                                           ; index is in rax & loop counter is in rcx

   mov  rdx, [hashtable + HashTable.metaArray]  ; array memory address
   add  rdx, rax
   add  rdx, MetadataElement.position          ; MetaElement field memory address

   push rcx

   mov  rcx, positionTextLen
   mov  rsi, positionText
   mov  eax, [printValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   push rbx
   push rdx
   mov  ax, [rdx]
   movzx rax, ax
   mov  rbx, positionVal
   call convertDigitsToText                     ; converts integers to text to print
   pop  rdx
   pop  rbx

   mov  ecx, [printValLen]
   mov  rsi, positionVal
   add  rbx, positionTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; print row meta element hash value
   add  rdx, MetadataElement.hashValue          ; MetaElement field memory address

   mov  rcx, hashTextLen
   mov  rsi, hashText
   mov  eax, [printValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   push rbx
   mov  ax, [rdx]
   movzx rax, ax
   mov  rbx, hashVal
   call convertDigitsToText                     ; converts integers to text to print
   pop  rbx

   mov  ecx, [printValLen]
   mov  rsi, hashVal
   add  rbx, hashTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; print row end text
   mov  rcx, endTextLen
   mov  rsi, endText
   mov  eax, [printValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   mov  eax, [printElementLen]
   mov  rbx, printTextLine
   call print

   pop rcx

   dec rcx
   jnz printHashTableElement

   ret

; Converts integers to text to print
; Input:
;     rax - integer value
;     rbx - variable memory address to store integer in text
; Output:
;     
convertDigitsToText:

   ; TODO: check bit length
   cmp  rax, 32768
   jl  positiveDigits

   ; TODO: check bit length
   xor  rax, 65535
   add  rax, 1
   push rax

   mov  rdi, rbx
   xor  rax, rax
   mov  rax, '-'
   stosb
   inc  rbx
   xor  rax, rax
   pop  rax

   positiveDigits:

      mov  rcx, 10
      mov  rbp, rsp
      xor  rdx, rdx
      
      splitDigit:
         
         div  rcx
         push rdx
         xor  rdx, rdx
         cmp  rax, 0
         jne  splitDigit

      appendDigit:

         mov  rdi, rbx
         
         pop  rax
         add  rax, '0'
         
         stosb
         inc  rbx

         cmp  rbp, rsp
         jne  appendDigit
   
   ret

; Prints insert textual message
; Input:
;     rax - value to insert in hash table
printInsertElement:

   ; pretty print insert message text
   mov  rcx, insertValTextLen
   mov  rsi, insertValText
   mov  rbx, insertPrintTextLine
   mov  rdi, rbx
   cld
   rep  movsb

   push rbx

   mov  rbx, insertVal
   call convertDigitsToText

   pop  rbx

   ; pretty print insert value
   mov  ecx, [insertPrintValLen]
   mov  rsi, insertVal
   add  rbx, insertValTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; pretty print insert message end text
   mov  rcx, insertEndTextLen
   mov  rsi, insertEndText
   mov  eax, [insertPrintValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   mov  eax, [insertPrintElementLen]
   mov  rbx, insertPrintTextLine
   call print

   ret

; Prints search textual message
; Input:
;     rax - value to search in hash table
;     rdx - position of the searched value in the hash table
printSearchElement:

   ; clean print variable before storing new values
   xor  rbx, rbx
   mov  [searchVal], rbx
   mov  [searchIdxVal], rbx

   ; pretty print search message text
   mov  rcx, searchValTextLen
   mov  rsi, searchValText
   mov  rbx, searchPrintTextLine
   mov  rdi, rbx
   cld
   rep  movsb

   push rbx
   push rdx

   ; pretty print search value
   mov  rbx, searchVal
   call convertDigitsToText

   pop  rdx
   pop  rbx

   mov  ecx, [searchPrintValLen]
   mov  rsi, searchVal
   add  rbx, searchValTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; pretty print search position message text
   mov  rcx, searchIdxTextLen
   mov  rsi, searchIdxText
   mov  eax, [searchPrintValLen]
   add rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   push  rbx

   ; pretty print search position value
   mov  rax, rdx
   mov  rbx, searchIdxVal
   call convertDigitsToText

   pop  rbx

   mov  ecx, [searchPrintValLen]
   mov  rsi, searchIdxVal
   add  rbx, searchIdxTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; pretty print search message end text
   mov  rcx, searchEndTextLen
   mov  rsi, searchEndText
   mov  eax, [searchPrintValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   mov  eax, [searchPrintElementLen]
   mov  rbx, searchPrintTextLine
   call print

   ret

; Prints delete textual message
; Input:
;     rax - value to delete in hash table
printDeleteElement:

   ; pretty print delete message text
   mov  rcx, deleteValTextLen
   mov  rsi, deleteValText
   mov  rbx, deletePrintTextLine
   mov  rdi, rbx
   cld
   rep  movsb

   push rbx

   ; pretty print delete value
   mov  rbx, deleteVal
   call convertDigitsToText

   pop  rbx

   mov  ecx, [deletePrintValLen]
   mov  rsi, deleteVal
   add  rbx, deleteValTextLen
   mov  rdi, rbx
   cld
   rep  movsb

   ; pretty print delete message end text
   mov  rcx, deleteEndTextLen
   mov  rsi, deleteEndText
   mov  eax, [deletePrintValLen]
   add  rbx, rax
   mov  rdi, rbx
   cld
   rep  movsb

   mov  eax, [deletePrintElementLen]
   mov  rbx, deletePrintTextLine
   call print

   ret

; Prints message to system out
; Input:
;     rax - length of the message to be printed
;     rbx - message to be printed
; Output:
;     
print:

   mov  rdx, rax        ;message length
   mov  rcx, rbx        ;message to write
   mov  rbx, STDOUT     ;file descriptor (stdout)
   mov  rax, SYS_WRITE  ;system call number (sys_write)
   int  0x80            ;call kernel
   ret

; Exits the program without errors
; Input:
;     
; Output:
;     
exit:
   mov  rax, SYS_EXIT   ;system call number (sys_exit)
   int  0x80            ;call kernel
   ret
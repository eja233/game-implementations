#lang racket
;; Elaine Arbaugh
;; 3/18/14
;; Implementation of some of the card game "klondike" in Racket Scheme
;; for a final in a class on programming methods. I was given a template,
;; but I wrote all the code except everything involving 'type and 'show. 
;; I didn't write the comments. This is not a full implementation.

;; Export all procedures defined in this module.
(provide (all-defined-out))



;; ---------------------------------------------------------------------
;; A playing card object.
;; ---------------------------------------------------------------------

;; Some helper functions that we require you to define.
;; You should use these below where appropriate.

;; Return #t if c is a card i.e. a message-passing object which 
;; responds 'card to the 'type message; otherwise return #f.
(define (card? c)
  (if (procedure? c)
      (if (eq? (c 'type) 'card)
          #t
          #f)
      #f))

;; Return the color of a suit: either 'red or 'black.
;; Suits are: 'c (clubs) 'd (diamonds) 'h (hearts) 's (spades)
;; Signal an error for invalid suits.
(define (color suit) 
  (cond ((or (eq? suit 'h) (eq? suit 'd)) 'red)
        ((or (eq? suit 'c) (eq? suit 's)) 'black)
        (else (error "Invalid suit"))))

;; Return the next rank of a particular rank.
;; Valid ranks are:
;; A (ace) 2 3 4 5 6 7 8 9 T (ten) J (jack) Q (queen) K (king)
;; Signal an error for invalid ranks, or if (next-rank 'K) is called.
(define (next-rank r)
  (cond ((eq? 'A r) 2)
        ((and (integer? r) (> 9 r) (< 1 r)) (+ r 1))
        ((eq? r 9) 'T)
        ((eq? r 'T) 'J)
        ((eq? r 'J) 'Q)
        ((eq? r 'Q) 'K)
        ((eq? r 'K) (error "King is highest card"))
        (else (error "Invalid card value"))))
         

;; Convert a rank to a string.
;; Note that a rank can be a number (2 3 4 5 6 7 8 9) or a symbol (A T J Q K).
;; Do not use a brute-force solution here or you will get no credit!
(define (rank->string r)
  (if (number? r)
      (number->string r)
      (symbol->string r)))

;; Make a message-passing card object.
;; card-data is a list with two elements: the rank 
;; (one of '(A 2 3 4 5 6 7 8 9 T J Q K))
;; and the suit (one of '(c d h s)).
;; Example: (make-card '(A h)) makes the Ace of hearts.
(define (make-card card-data)
  (let ((rank (car card-data))
        (suit (cadr card-data)))
    (lambda (op . args)
      (cond ((eq? op 'type) 'card)
            ((eq? op 'rank) rank)
            ((eq? op 'suit) suit)
            ((eq? op 'color) (color suit))
            
            ((eq? op 'next-higher-by-rank?)
             (eq? rank (next-rank (car args))))
            
            ((eq? op 'next-lower-by-color?)
             (and (eq? ((car args) 'rank) (next-rank rank))
                  (not (eq? (color suit) ((car args) 'color)))))
            
            ((eq? op 'show)
             (string-append 
              "[" (rank->string rank) (symbol->string suit) "]"))
            
            (else (error "card: unknown operation: " op))))))

;; ---------------------------------------------------------------------
;; An object representing a deck of 52 playing cards.
;; ---------------------------------------------------------------------

;; Return a full deck of 52 cards, 
;; where each card is a message-passing object.  
;; NOTE: Do not use a brute-force solution here, or you will get no credit!
;; NOTE: This function is required and you should use it in the make-deck
;; procedure.
;; HINT: apply, append, and map will be useful.
(define (all-cards)
  (let ((ranks '(A 2 3 4 5 6 7 8 9 T J Q K)))
    (append
     (map (lambda (x) (make-card (list x 'd))) ranks)
     (map (lambda (x) (make-card (list x 's))) ranks)
     (map (lambda (x) (make-card (list x 'h))) ranks)
     (map (lambda (x) (make-card (list x 'c))) ranks))))

;; Make the deck-of-cards message-passing object.
(define (make-deck)
 (let ((current (shuffle (all-cards))))
   (define (remove n)
     (if (= n 0)
         (list)
         (let ((top (car current)))
           (begin 
             (set! current (cdr current))
             (cons top (remove (- n 1)))))))
    (lambda (op . args)
      (cond ((eq? op 'type) 'deck)
            ((eq? op 'deal)
             (if (< (length current) (car args))
                 (list #f "Not enough cards")
                 (list #t (remove (car args)))))            
            ((eq? op 'rest)
             (let ((rest current))
               (begin (set! current (list))
                      rest)))
            
            (else (error "deck: unknown operation: " op))))))

;; ---------------------------------------------------------------------
;; An object representing the stock.
;; ---------------------------------------------------------------------

(define (make-stock cards)
  (let ((hidden cards)
        (visible (list)))
    (lambda (op . args)
      (cond ((eq? op 'type) 'stock)
            
            ((eq? op 'take-card)
             (if (> (length visible) 0)
                 (let ((top (car visible)))
                   (begin 
                     (set! visible (cdr visible))
                     (list #t top)))
                 (list #f "Not enough cards")))
             
            
            ((eq? op 'undo-take-card)
             (set! visible (cons (car args) visible)))
            
            ((eq? op 'next)
             (if (> (length hidden) 0)
                 (begin (set! visible (cons (car hidden) visible))
                        (set! hidden (cdr hidden))
                        (list #t))
                 (#f "No more face-down cards")))
            
            ((eq? op 'restock)
             (if (= (length hidden) 0)
                 (begin (set! hidden (reverse visible))
                        (set! visible (list)) 
                        (list #t))
                 (list #f "Can't restock until face-down cards exhausted")))
            
            ((eq? op 'show)
             (string-append "STOCK: "
                            (if (null? visible)
                                "[--]"
                                ((car visible) 'show))
                            "    face down cards: "
                            (number->string (length hidden))
                            "    face up cards: "
                            (number->string (length visible))
                            ))
            
            (else (error "stock: unknown operation: " op))))))

;; ---------------------------------------------------------------------
;; An object representing the foundation.
;; ---------------------------------------------------------------------

(define (make-foundation)
  (define (show-suit suits n)
    (let ((r (vector-ref suits n)))
      (if (eq? r #f) "-" (rank->string r))))
  
  ;; Other helper functions can go here.
  
  (let ((suits (vector #f #f #f #f)))
    ;; Helper functions can go here if they depend on the suits vector.
    (lambda (op . args)
      (cond ((eq? op 'type) 'foundation)
            
            ((eq? op 'store)
             (let ((c (car args)))
             (if (card? c)
                 (cond ((eq? (c 'suit) 'c)
                        (if (eq? (vector-ref suits 0) #f)
                            (if (eq? (c 'rank) 'A)
                                (begin 
                                  (vector-set! suits 0 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))
                            (if (c 'next-higher-by-rank? (vector-ref suits 0))
                                (begin 
                                  (vector-set! suits 0 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))))
                       ((eq? (c 'suit) 'd)
                        (if (eq? (vector-ref suits 1) #f)
                            (if (eq? (c 'rank) 'A)
                                (begin 
                                  (vector-set! suits 1 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))
                            (if (c 'next-higher-by-rank? (vector-ref suits 1))
                                (begin 
                                  (vector-set! suits 1 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))))
                       ((eq? (c 'suit) 'h)
                        (if (eq? (vector-ref suits 2) #f)
                            (if (eq? (c 'rank) 'A)
                                (begin 
                                  (vector-set! suits 2 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))
                            (if (c 'next-higher-by-rank? (vector-ref suits 2))
                                (begin 
                                  (vector-set! suits 2 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))))
                       ((eq? (c 'suit) 's)
                        (if (eq? (vector-ref suits 3) #f)
                            (if (eq? (c 'rank) 'A)
                                (begin 
                                  (vector-set! suits 3 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))
                            (if (c 'next-higher-by-rank? (vector-ref suits 3))
                                (begin 
                                  (vector-set! suits 3 (c 'rank))
                                  (list #t))
                                (list #f "Can't store card on foundation"))))
                       (else
                        (list #f "Can't store card on foundation")))
                 (list #f "Can't store a non-card on foundation"))))
            
            ((eq? op 'done?)
             (if (and 
                  (eq? (vector-ref suits 0) 'K)
                  (eq? (vector-ref suits 1) 'K)
                  (eq? (vector-ref suits 2) 'K)
                  (eq? (vector-ref suits 3) 'K))
                 #t
                 #f))
            
            ((eq? op 'show)
             (string-append "FOUNDATION: ["
                            (show-suit suits 0) "c] ["
                            (show-suit suits 1) "d] ["
                            (show-suit suits 2) "h] ["
                            (show-suit suits 3) "s]"))
            
            (else (error "foundation: unknown operation: " op))))))

;; ---------------------------------------------------------------------
;; An object representing one column on the game tableaux.
;; ---------------------------------------------------------------------

;; Helper function to determine if a list of cards is an alternating
;; sequence (ascending ranks, switching colors each card).
;; NOTE: This function is required and you should use it in the make-column
;; procedure.
(define (alternating-sequence? cards)
  (cond ((null? cards) #t)
        ((eq? (length cards) 1) #t)
        (else 
         (if ((car cards) 'next-lower-by-color? (cadr cards))
             (alternating-sequence? (cdr cards))
             #f))))

;; Make a column given a list of cards.
(define (make-column cards)
  ;; Check that the list of cards is in fact a list of cards.
  (if (not (and (> (length cards) 0) (andmap card? cards)))
      (error "make-column: invalid argument: " cards)
      (let ((hidden (cdr cards))
            (visible (list (car cards))))
        
        (define (remove-visible n)
         (if (= n 0)
             (list)
             (let ((top (car visible)))
               (begin 
                 (set! visible (cdr visible))
                 (cons top (remove-visible (- n 1)))))))
        (lambda (op . args)
          (cond ((eq? op 'type) 'column)
                
                ((eq? op 'remove-from-top)
                 (let ((number (car args)))
                   (if (> number (length visible))
                       (list #f "Not enough cards")
                       (let ((removed (remove-visible number)))
                         (if (alternating-sequence? removed)
                             (list #t removed)
                             (list #f "Cards aren't an alternating sequence"))))))
                
                ((eq? op 'undo-remove-from-top)
                 (set! visible (append (car args) visible)))
                
                ((eq? op 'add-to-top)
                 (let ((cards (car args)))
                   (if (pair? cards)
                       (if (card? (car cards))
                           (if (alternating-sequence? cards)
                               (if (eq? ((car (reverse cards)) 'rank) 'K)
                                   (if (null? visible)
                                       (begin 
                                         (set! visible cards)
                                         (list #t))
                                       (list #f "King can only go on empty space"))
                                   (if (null? visible)
                                       (list #f "Only kings can be placed on empty spaces")
                                       (if ((car (reverse cards)) 'next-lower-by-color? (car visible))
                                           (begin
                                             (set! visible
                                                   (append cards visible))
                                             (list #t))
                                           (list #f "Cards can't be placed there"))))
                               (list #f "Cards must form an alternating sequence"))
                           (list #f "Input must be cards"))
                       (list #f "Input must be a list"))))
                                         
                               
                
                ((eq? op 'adjust)
                 (cond ((and (= (length visible) 0)
                             (> (length hidden) 0))
                        (begin (set! visible (list (car hidden)))
                                (set! hidden (cdr hidden))))))
                
                ((eq? op 'show)
                 (append (map (lambda (c) "[**]") hidden)
                         (reverse (map (lambda (c) (c 'show)) visible))))
                
                (else (error "column: unknown operation: " op)))))))

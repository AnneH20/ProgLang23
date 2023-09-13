;;;===================================================================================================
;;;     CSE 4714 - Theory and Implementation of Programming Languages CLIPS Extra Credit Assignment
;;;
;;;     AFC Football Teams System - Anne Marie Heidebreicht (alh1310)
;;;
;;;     A simple expert system which attempts to identify a NFL football team based off the 
;;;     team's various characteristics. The CLIPS IDE will ask various yes or no questions. 
;;;     The user will think of a NFL (preferably AFC) team and answer based on their knowledge of
;;;     that team. The system will print out the team the user was thinking of. If you think of an
;;;     AFC team, the system will pinpoint the exact team. If you think of a NFC team, the system will
;;;     simply output that it knows your are thinking of a NFC team; however, it will not pinpoint the
;;;     team precisely. It only precisely guesses an AFC team.
;;;     
;;;     Source used: https://github.com/noxdafox/clips/blob/master/examples/animal.clp
;;;
;;;     CLIPS Version 6.4 Example
;;; 
;;;     To execute, load, reset, and run.
;;;     To re-execute, hit reset and run again.
;;;===================================================================================================

(defmodule MAIN (export ?ALL)) 

(defmodule VALIDATE (import MAIN ?ALL))

(defmodule CHAIN (import MAIN ?ALL))

(defmodule ASK (import MAIN ?ALL))

;;;*************************
;;;* DEFGLOBAL DEFINITIONS *
;;;*************************

(defglobal MAIN
   ?*rule-index* = 1
   ?*validate* = TRUE)

;;;***************************
;;;* DEFFUNCTION DEFINITIONS *
;;;***************************

(deffunction generate-rule-name ()
   (bind ?name (sym-cat rule- ?*rule-index*))
   (bind ?*rule-index* (+ ?*rule-index* 1))
   (return ?name))

;;;***************************
;;;* DEFTEMPLATE DEFINITIONS *
;;;***************************

(deftemplate MAIN::rule 
   (slot name (default-dynamic (generate-rule-name)))
   (slot validate (default no))
   (multislot if)
   (multislot then)
   (multislot processed))
   
(deftemplate MAIN::question
   (multislot valid-answers)
   (slot variable)
   (slot query))

(deftemplate MAIN::answer
   (slot variable)
   (slot prefix (default ""))
   (slot postfix (default "")))
   
(deftemplate MAIN::goal
   (slot variable))
   
(deftemplate MAIN::variable
   (slot name)
   (slot value))
   
(deftemplate MAIN::activity)

(deftemplate MAIN::legalanswers
   (multislot values))
   
;;;**************************
;;;* INFERENCE ENGINE RULES *
;;;**************************

(defrule MAIN::startup
   =>
   (if ?*validate*
      then
      (focus VALIDATE CHAIN ASK)
      else
      (focus CHAIN ASK)))
   
(defrule MAIN::continue
   (declare (salience -10))
   ?f <- (activity)
   =>
   (retract ?f)
   (focus CHAIN ASK))
   
(defrule MAIN::goal-satified ""
   (goal (variable ?goal))
   (variable (name ?goal) (value ?value))
   (answer (prefix ?prefix) (postfix ?postfix) (variable ?goal))
   =>
   (println ?prefix ?value ?postfix))

;;; ##################
;;; CHAIN MODULE RULES 
;;; ##################

(defrule CHAIN::propagate-goal ""
   (logical (goal (variable ?goal))
            (rule (if ?variable $?)
                  (then ?goal ? ?value)))
   =>
   (assert (goal (variable ?variable))))

(defrule CHAIN::modify-rule-match-is ""
   (variable (name ?variable) (value ?value))
   ?f <- (rule (if ?variable is ?value and $?rest)
               (processed $?p))
   =>
   (modify ?f (if ?rest)
              (processed ?p ?variable is ?value and)))

(defrule CHAIN::rule-satisfied-is ""
   (variable (name ?variable) (value ?value))
   ?f <- (rule (if ?variable is ?value)
               (then ?goal ? ?goal-value)
               (processed $?p))
   =>
   (modify ?f (if) 
              (processed ?p ?variable is ?value #)))
              
(defrule CHAIN::apply-rule ""
   (logical (rule (if)
                  (then ?goal ? ?goal-value)))
   =>
   (assert (variable (name ?goal) (value ?goal-value))))

;;; ################
;;; ASK MODULE RULES 
;;; ################

(defrule ASK::ask-question-no-legalvalues ""
   (not (legalanswers))
   ?f1 <- (goal (variable ?variable))
   (question (variable ?variable) (query ?text))
   (not (variable (name ?variable)))
   =>
   (assert (activity))
   (retract ?f1)
   (print ?text " ")
   (assert (variable (name ?variable) (value (read)))))

(defrule ASK::ask-question-legalvalues ""
   (legalanswers (values $?answers))
   ?f1 <- (goal (variable ?variable))
   (question (variable ?variable) (query ?text))
   (not (variable (name ?variable)))
   =>
   (assert (activity))
   (retract ?f1)
   (print ?text " ")
   (print ?answers " ")
   (bind ?reply (read))
   (if (lexemep ?reply)
      then
      (bind ?reply (lowcase ?reply)))
   (if (member$ ?reply ?answers) 
     then (assert (variable (name ?variable) (value ?reply)))
     else (assert (goal (variable ?variable)))))

;;; #####################
;;; VALIDATE MODULE RULES 
;;; #####################
      
(defrule VALIDATE::copy-rule
   (declare (salience 10))
   ?f <- (rule (validate no))
   =>
   (duplicate ?f (validate yes))
   (modify ?f (validate done)))

(defrule VALIDATE::next-condition
   (declare (salience -10))
   ?f <- (rule (name ?name) (validate yes)
               (if ?a ?c ?v and $?rest))
   =>
   (modify ?f (if ?rest)))
   
(defrule VALIDATE::validation-complete
   (declare (salience -10))
   ?f <- (rule (validate yes) (if ? ? ?))
   =>
   (retract ?f))

;;; *******************
;;; Validation - Syntax
;;; *******************

(defrule VALIDATE::and-connector
   ?f <- (rule (name ?name) (validate yes)
               (if ?a ?c ?v ?connector&~and $?))
   =>
   (retract ?f)
   (println "In rule " ?name ", if conditions must be connected using and:" crlf
            "   " ?a " " ?c " " ?v " *" ?connector "*"))

(defrule VALIDATE::and-requires-additional-condition
   ?f <- (rule (name ?name) (validate yes)
               (if ?a ?c ?v and))
   =>
   (retract ?f)
   (println "In rule " ?name ", an additional condition should follow the final and:" crlf
            "   " ?a " " ?c " " ?v " and <missing condition>"))
               
(defrule VALIDATE::incorrect-number-of-then-terms          
   ?f <- (rule (name ?name) (validate yes)
               (then $?terms&:(<> (length$ ?terms) 3)))
   =>
   (retract ?f)
   (println "In rule " ?name ", then portion should be of the form <variable> is <value>:" crlf
            "   " (implode$ ?terms)))

(defrule VALIDATE::incorrect-number-of-if-terms          
   ?f <- (rule (name ?name) (validate yes)
               (if $?terms&:(< (length$ ?terms) 3)))
   =>
   (retract ?f)
   (println "In rule " ?name ", if portion contains an incomplete condition:" crlf
            "   " (implode$ ?terms)))

(defrule VALIDATE::incorrect-then-term-syntax          
   ?f <- (rule (name ?name) (validate yes)
               (then ?a ?c&~is ?v))
   =>
   (retract ?f)
   (println "In rule " ?name ", then portion should be of the form <variable> is <value>:" crlf
            "   " ?a " " ?c " " ?v " "))

(defrule VALIDATE::incorrect-if-term-syntax          
   ?f <- (rule (name ?name) (validate yes)
               (if ?a ?c&~is ?v $?))
   =>
   (retract ?f)
   (println "In rule " ?name ", if portion comparator should be \"is\"" crlf
            "   " ?a " " ?c " " ?v " "))
               
(defrule VALIDATE::illegal-variable-value
   ?f <- (rule (name ?name) (validate yes)
               (if ?a ?c ?v $?))
   (question (variable ?a) (valid-answers))
   (legalanswers (values $?values))
   (test (not (member$ ?v ?values)))
   =>
   (retract ?f)
   (println "In rule " ?name ", the value " ?v " is not legal for variable " ?a ":" crlf
            "   " ?a " " ?c " " ?v))               

(defrule VALIDATE::reachable
   (rule (name ?name) (validate yes)
         (if ?a ?c ?v $?))
   (not (question (variable ?a)))
   (not (rule (then ?a $?)))
   =>
   (println "In rule " ?name " no question or rule could be found "
               "that can supply a value for the variable " ?a ":" crlf
               "   " ?a " " ?c " " ?v))

(defrule VALIDATE::used "TBD lower salience"
   ?f <- (rule (name ?name) (validate yes)
               (then ?a is ?v))
   (not (goal (variable ?a)))
   (not (rule (if ?a ? ?v $?)))
   =>
   (retract ?f)
   (println "In rule " ?name " the conclusion for variable " ?a 
            " is neither referenced by any rules nor the primary goal" crlf
            "   " ?a " is " ?v))
               
(defrule VALIDATE::variable-in-both-if-and-then
   ?f <- (rule (name ?name) (validate yes)
               (if ?a $?)
               (then ?a is ?v))
   =>
   (retract ?f)
   (println "In rule " ?name " the variable " ?a 
            " is used in both the if and then sections"))
                              
(defrule VALIDATE::question-variable-unreferenced
   (question (variable ?a) (query ?q))
   (not (rule (validate done) (if $? ?a is ?v $?)))
   =>
   (println "The question \"" ?q "\", assigns a value to the variable " ?a 
            " which is not referenced by any rules"))

;;;***************************
;;;* DEFFACTS KNOWLEDGE BASE *
;;;***************************

(deffacts MAIN::knowledge-base 
   (goal (variable type.nflteam))
   (legalanswers (values yes no))
   (question (variable AFCslocation)
             (query "Is your team in the AFC South?"))
   (rule (if AFCslocation is yes)
         (then location is afcS))
   (rule (if AFCslocation is no)
         (then location is afcO))
   (question (variable colors)
             (query "Does your team have red and blue in their colors?"))
   (rule (if location is afcS and colors is yes)
         (then teamName is startswT))
   (question (variable mascot)
             (query "Is your team's mascot a raccoon?"))
   (rule (if teamName is startswT and mascot is yes)
         (then type.nflteam is Titans))
   (rule (if teamName is startswT and mascot is no)
         (then type.nflteam is Texans))
   (rule (if location is afcS and colors is no)
         (then teamName is othersT))
   (question (variable mascot2)
             (query "Is your team's mascot a horse?"))
   (rule (if teamName is othersT and mascot2 is yes)
         (then type.nflteam is Colts))
   (rule (if teamName is othersT and mascot2 is no)
         (then type.nflteam is Jaguars))
   (question (variable AFCnlocation)
             (query "Is your team in the AFC North?"))
   (rule (if location is afcO and AFCnlocation is yes)
         (then location2 is afcN))
   (rule (if location is afcO and AFCnlocation is no)
         (then location2 is afcO2))
   (question (variable city)
             (query "Is your team located in Ohio?"))
   (rule (if location2 is afcN and city is yes)
         (then teamColor is orange))
   (question (variable mascot3)
             (query "Is your team's mascot a tiger?"))
   (rule (if teamColor is orange and mascot3 is yes)
         (then type.nflteam is Bengals))
   (rule (if teamColor is orange and mascot3 is no)
         (then type.nflteam is Browns))
   (rule (if location2 is afcN and city is no)
         (then teams is other))
   (question (variable color)
             (query "Does your team have purple in their colors?"))
   (rule (if teams is other and color is yes)
         (then type.nflteam is Ravens))
   (rule (if teams is other and color is no)
         (then type.nflteam is Steelers))
   (question (variable AFCelocation)
             (query "Is your team in the AFC East?"))
   (rule (if location2 is afcO2 and AFCelocation is yes)
         (then location3 is afcE))
   (rule (if location2 is afcO2 and AFCelocation is no)
         (then location3 is afcW))
   (question (variable city2)
             (query "Is your team location in New York?"))
   (rule (if location3 is afcE and city2 is yes)
         (then team2 is nyc))
   (rule (if location3 is afcE and city2 is no)
         (then team2 is other))
   (question (variable animal)
             (query "Is your team's mascot an animal?"))
   (rule (if team2 is nyc and animal is yes)
         (then type.nflteam is Bills))
   (rule (if team2 is nyc and animal is no)
         (then type.nflteam is Jets))
   (question (variable dolphin)
             (query "Is your team's mascot a dolphin?"))
   (rule (if team2 is other and dolphin is yes)
         (then type.nflteam is Dolphins))
   (rule (if team2 is other and dolphin is no)
         (then type.nflteam is Patriots))
   (question (variable AFCwlocation)
             (query "Is your team in the AFC West?"))
   (rule (if location3 is afcW and AFCwlocation is yes)
         (then location4 is afcW))
   (rule (if location3 is afcW and AFCwlocation is no)
         (then location4 is nfc))
   (question (variable superbowl)
             (query "Has your team won a Super Bowl in the last 20 years?"))
   (rule (if location4 is afcW and superbowl is yes)
         (then team3 is winners))
   (rule (if location4 is afcW and superbowl is no)
         (then team3 is losers))
   (question (variable rado)
             (query "Is your team located in Colorado?"))
   (rule (if team3 is winners and rado is yes)
         (then type.nflteam is Broncos))
   (rule (if team3 is winners and rado is no)
         (then type.nflteam is Chiefs))
   (question (variable cali)
             (query "Is your team located in California?"))
   (rule (if team3 is losers and cali is yes)
         (then type.nflteam is Chargers))
   (rule (if team3 is losers and cali is no)
         (then type.nflteam is Raiders))
   (rule (if location4 is nfc)
         (then type.nflteam is teamsInTheNFC))
   (answer (prefix "I think your team is the ") (variable type.nflteam) (postfix ".")))
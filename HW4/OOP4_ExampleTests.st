OOPObject subclass: #Dog
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'OOP4_ExampleTests'!

!Dog methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:37'!
bark
	AssertionFailure signal: 'in Dog bark'! !


TestCase subclass: #ExampleTests
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'OOP4_ExampleTests'!

!ExampleTests methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:35'!
setUp
	(Smalltalk hasClassNamed: #Dog) ifTrue: [Smalltalk removeClassNamed: #Dog].
	(Smalltalk hasClassNamed: #Pet) ifTrue: [Smalltalk removeClassNamed: #Pet].
	(Smalltalk hasClassNamed: #Terrier) ifTrue: [Smalltalk removeClassNamed: #Terrier].
	(Smalltalk hasClassNamed: #Rock) ifTrue: [Smalltalk removeClassNamed: #Rock].	
	
	OOPObject subclass: #Dog
				    parentClasses: {}
				    instanceVariableNames: ''
				    classVariableNames: ''
				    poolDictionaries: ''
				    category: 'OOP4_ExampleTests'.

	Dog compile: 
	'bark
	AssertionFailure signal: ''in Dog bark'''.

	OOPObject subclass: #Pet
				    parentClasses: {}
				    instanceVariableNames: ''
				    classVariableNames: ''
				    poolDictionaries: ''
				    category: 'OOP4_ExampleTests'.

	Pet compile: 
	'nickname
	AssertionFailure signal: ''in Pet nickname'''.

	OOPObject subclass: #Terrier
				    parentClasses: {OOPParent new parentClass: Dog; inheritanceType: 'protected'.
											OOPParent new parentClass: Pet; inheritanceType: 'public'}
				    instanceVariableNames: 'roots'
				    classVariableNames: ''
				    poolDictionaries: ''
				    category: 'OOP4_ExampleTests'.	

	OOPObject subclass: #Rock
				    parentClasses: {}
				    instanceVariableNames: ''
				    classVariableNames: ''
				    poolDictionaries: ''
				    category: 'OOP4_ExampleTests'.	

	Rock compile: 
	'noAccess
	Terrier new bark'.

	Rock compile: 
	'okAccess
	Terrier new nickname'.! !

!ExampleTests methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:36'!
testClassify
	self assert: (Terrier classifyInheritedMethod: #bark) = 'protected'.
	self assert: (Terrier classifyInheritedMethod: #nickname) = 'public'.	
	self assert: (Terrier classifyInheritedMethod: #other) = 'undefined'.		! !

!ExampleTests methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:36'!
testMethodSending
| rock dog text|
	text := ''.
	dog := Dog new.
	rock := Rock new.

	[dog bark] on: AssertionFailure do: [:err| text := err messageText ].
	self assert: (text = 'in Dog bark').	

	[rock okAccess] on: AssertionFailure do: [:err| text := err messageText ].
	self assert: (text = 'in Pet nickname').

	[rock noAccess] on: AssertionFailure do: [:err| text := err messageText ].
	self assert: (text = 'Rock cannot send bark to Terrier because: protected').! !


OOPObject subclass: #Pet
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'OOP4_ExampleTests'!

!Pet methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:37'!
nickname
	AssertionFailure signal: 'in Pet nickname'! !


OOPObject subclass: #Rock
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'OOP4_ExampleTests'!

!Rock methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:37'!
noAccess
	Terrier new bark! !

!Rock methodsFor: 'as yet unclassified' stamp: 'OC 5/25/2018 12:37'!
okAccess
	Terrier new nickname! !


OOPObject subclass: #Terrier
	instanceVariableNames: 'roots'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'OOP4_ExampleTests'!

module RosettaJSON.Types
	( JSONValue(..)) where

data JSONValue
	= JSONNull
	| JSONBool Bool
	| JSONNumber Double
	| JSONString String
	| JSONArray [JSONValue]
	| JSONObject [(String, JSONValue)]
	deriving (Eq, Show)

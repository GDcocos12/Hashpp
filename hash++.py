import binascii

def encrypt(string, key):
	#preparing
	s = string
	ss = s[::-1]
	decstr = []

	[decstr.append(ord(c)) for c in ss]

	for p in range(len(decstr)):
		decstr[p] += key

	respdec = ''.join(chr(i) for i in decstr)

	sj = bin(int.from_bytes(respdec.encode(), 'big'))

	#encoding into hash++
	output = ""
	zero = 0
	ones = 0
	for i in str(sj):
		if i == "0":
			if zero == 2:
				output += "#"
				zero = 0
			else:
				output += "!"
				zero += 1
		elif i == "1":
			if ones == 2:
				output += "z"
				ones = 0
			else:
				output += "+"
				ones += 1

	return output

def decrypt(string, key):
	s = ""
	for i in string:
		if i == "#" or i == "!":
			s += "0"
		elif i == "z" or i == "+":
			s += "1"

	str_data = ""
	decstr = []

	b = int(s, 2)
	str_data = b.to_bytes((b.bit_length() + 7) // 8, 'big').decode()

	[decstr.append(ord(c)) for c in str_data]
	
	for o in range(len(decstr)):
		decstr[o] -= key

	respdec = ''.join(chr(i) for i in decstr)

	finaloutput = respdec[::-1]

	return finaloutput

mode = int(input("Mode(1 - encrypt, 2 - decrypt): "))
if mode == 1:
	stri = input("String to encode: ")
	key = int(input("Key: "))
	print(encrypt(stri, key))
elif mode == 2:
	stri = input("Code: ")
	key = int(input("Key(Enter the key that the string is encoded with): "))
	print(decrypt(stri, key))
else:
	print("Error! Mode not found!")
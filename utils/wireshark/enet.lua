
enet_proto = Proto("enet", "ENET LoL UDP Protocol")

MAX_ITEM_LABEL_LENGTH = 240
MIN_PORT = 5000
MAX_PORT = 6000

b64key = ""
b64keyfile = ""

package.cpath = package.cpath .. ";" .. USER_DIR .. "plugins\\enet\\?.dll"

require "blowfish"

command2string = {
	[0] = "NONE",
	[1] = "ACKNOWLEDGE",
	[2] = "CONNECT",
	[3] = "VERIFY_CONNECT",
	[4] = "DISCONNECT",
	[5] = "PING",
	[6] = "SEND_RELIABLE",
	[7] = "SEND_UNRELIABLE",
	[8] = "SEND_FRAGMENT",
	[9] = "SEND_UNSEQUENCED",
	[10] = "BANDWIDTH_LIMIT",
	[11] = "THROTTLE_CONFIGURE",
	[99] = "UNKNOWN COMMAND (THIS IS AN ERROR)",
}
pf_seqnumber = ProtoField.new("Sequence number", "enet_proto.seqnumber", ftypes.UINT16)
pf_command = ProtoField.new("Command", "enet_proto.command", ftypes.UINT8, command2string, base.DEC, 0x0f)
pf_channel = ProtoField.new("ChannelID", "enet_proto.channel", ftypes.UINT8)
pf_header = ProtoField.new("ENET Header", "enet_proto.header", ftypes.BYTES, nil, base.NONE)
pf_dataLength = ProtoField.new("Data length", "enet_proto.dataLength", ftypes.UINT16)
pf_data = ProtoField.new("LoL Data", "enet_proto.data", ftypes.BYTES)
pf_datas = ProtoField.new("LoL Decrypted Data", "enet_proto.datas", ftypes.STRING)
pf_key = ProtoField.new("LoL Game Key", "enet_proto.key", ftypes.STRING)
enet_proto.fields = {
	pf_seqnumber,
	pf_command,
	pf_channel,
	pf_header,
	pf_dataLength,
	pf_data,
	pf_datas,
	pf_key
}

lolcmds = {
	[0x00] = "KeyCheck",
	[0x0b] = "RemoveItem",
	
	[0x11] = "S2C_EndSpawn",
	[0x14] = "C2S_QueryStatusReq",
	[0x15] = "S2C_SkillUp",
	[0x16] = "C2S_Ping_Load_Info",
	[0x1A] = "S2C_AutoAttack",
	
	[0x20] = "C2S_SwapItems",
	[0x23] = "S2C_FogUpdate2",
	[0x2A] = "S2C_PlayerInfo",
	[0x2C] = "S2C_ViewAns",
	[0x2E] = "C2S_ViewReq",
	
	[0x39] = "C2S_SkillUp",
	[0x3B] = "S2C_SpawnProjectile",
	[0x3E] = "S2C_SwapItems",
	[0x3F] = "S2C_LevelUp",
	
	[0x40] = "S2C_AttentionPing",
	[0x42] = "S2C_Emotion",
	[0x48] = "C2S_Emotion",
	[0x4C] = "S2C_HeroSpawn",
	[0x4D] = "S2C_Announce",
	
	[0x52] = "C2S_StartGame",
	[0x54] = "S2C_SynchVersion",
	[0x56] = "C2S_ScoreBord",
	[0x57] = "C2S_AttentionPing",
	[0x5A] = "S2C_DestroyProjectile",
	[0x5C] = "C2S_StartGame",
	
	[0x62] = "S2C_StartSpawn",
	[0x64] = "C2S_ClientReady",
	[0x65] = "S2C_LoadHero",
	[0x66] = "S2C_LoadName",
	[0x67] = "S2C_LoadScreenInfo",
	[0x68] = "ChatBoxMessage",
	[0x6A] = "S2C_SetTarget",
	[0x6F] = "S2C_BuyItemAns",
	
	[0x72] = "C2S_MoveReq",
	[0x77] = "C2S_MoveConfirm",
	
	[0x81] = "C2S_LockCamera",
	[0x82] = "C2S_BuyItemReq",
	[0x87] = "S2C_SpawnParticle",
	[0x88] = "S2C_QueryStatusAns",
	[0x8F] = "C2S_Exit",
	
	[0x92] = "SendGameNumber",
	[0x95] = "S2C_Ping_Load_Info",
	[0x9A] = "C2S_CastSpell",
	[0x9D] = "S2C_TurretSpawn",
	
	[0xA4] = "C2S_Surrender",
	[0xA8] = "C2S_StatsConfirm",
	[0xAE] = "S2C_SetHealth",
	[0xAF] = "C2S_Click",
	
	[0xB5] = "S2C_CastSpellAns",
	[0xBA] = "S2C_MinionSpawn",
	[0xBD] = "C2S_SynchVersion",
	[0xBE] = "C2S_CharLoaded",
	
	[0xC0] = "S2C_GameTimer",
	[0xC1] = "S2C_GameTimerUpdate",
	[0xC4] = "S2C_CharStats",
	
	[0xD0] = "S2C_LevelPropSpawn",
	
	[0xFF] = "Batch"
}

--[[
	the core dissector:
	tvbuf -> Tvb object
	pktinfo -> Pinfo object
	root -> TreeItem object 
--]]
function enet_proto.dissector(tvbuf, pktinfo, root)

	pktinfo.cols.protocol = "ENET"
	
	pktlen = tvbuf:reported_length_remaining()
	
	tree = root:add(enet_proto, tvbuf:range(0,pktlen))
	
	header = tree:add(pf_header, tvbuf:range(0,8))
	
	seqnumber = tvbuf:range(2,2)
	header:add(pf_seqnumber, seqnumber)
	
	command = tvbuf:range(4,1):bitfield(4,4)
	if command >= 0 and command <= 11 then
		header:add(pf_command, tvbuf:range(4,1))
	else
		print("unknown command")
		command = 99
	end
	
	pktinfo.cols.info = command2string[command]
	
	channel = tvbuf:range(5,1)
	header:add(pf_channel, channel)
	
	if command == 6 then
	
		loltree = root:add(pf_data, tvbuf:range(10, pktlen - 10))
		loltree:set_text("LoL Data")
		
		if b64key == "" then
			loltree:add(pf_key, "No key found" .. " (" .. b64keyfile .. ")")
			return
		end
		
		loltree:add(pf_key, b64key .. " (" .. b64keyfile .. ")")
	
		coverage = 10
		
		while coverage < pktlen do
		
			dataLength = tvbuf:range(coverage-2,2)
			loltree:add(pf_dataLength, dataLength)
			
			data = tvbuf:range(coverage, dataLength:uint())
			
			dataTemp = {}
			
			for i=0, dataLength:uint()-1 do
				dataTemp[i] = tvbuf:range(coverage+i, 1):uint()
			end
			
			decryptedData = bf_Decrypt(dataTemp, dataLength:uint())
			
			decryptedByteArray = ByteArray.new()
			decryptedHexString = ""
			decryptedByteArray:set_size(dataLength:uint())
			for i=0, dataLength:uint()-1 do
				decryptedByteArray:set_index(i, decryptedData[i])
				decryptedHexString = decryptedHexString .. string.format("%x ", decryptedData[i])
			end
			
			lolcmd = decryptedByteArray:get_index(0)
			if lolcmds[lolcmd] ~= nil then
				pktinfo.cols.info:append(" " .. lolcmds[lolcmd])
			end
			
			loltree:add(pf_datas, tvbuf:range(coverage, dataLength:uint()), decryptedHexString)
			
			coverage = coverage + dataLength:uint()
			
			if coverage < pktlen and 
			( tvbuf:range(coverage, 1):uint() == 0x07 or tvbuf:range(coverage, 1):uint() == 0x49 ) then
				coverage = coverage + 8
			else
				coverage = coverage + 6
			end
			
		end
		
	end
	
end

-- load the udp.port table
-- udp_table = DissectorTable.get("udp.port")

-- register our protocol to handle one specific udp port
-- udp_table:add(5100, enet_proto)

--[[
	a heuristic to decide if the ENET dissector should handle the data
	sadly its broken, u cannot return true here (wireshark.exe crashes, tshark.exe is doing fine!)
	but if you set the enet protocol for the rest of the conversation and return false,
	somehow it works as intended
--]]
function heur_dissect_enet(tvbuf, pktinfo, root)
	print("heur_dissect_enet")
	
	tvbr = tvbuf:range(0,1)
	if tvbr:uint() == 41 then
		print("found the first byte to be 0x29 (dec: 41), its ENET")
	else
		if pktinfo.src_port > MIN_PORT and pktinfo.src_port < MAX_PORT then

		else
			if pktinfo.dst_port > MIN_PORT and pktinfo.dst_port < MAX_PORT then

			else
				return false
			end
		end
	end
	
	-- generate a filename/identifier for this capture
	-- wireshark doesnt provide the .pcap filename in LUA (why?)
	-- one cannot add data to the capture file
	-- only other approach would be using Prefs :/
	
	-- data for id: absolute time of capture, server port, server adress
	
	--print(pktinfo.abs_ts)
	--print(pktinfo.src)
	--print(pktinfo.dst)
	
	id_port = 0
	if pktinfo.src_port > MIN_PORT and pktinfo.src_port < MAX_PORT then
		id_port = pktinfo.src_port
	end
	if pktinfo.dst_port > MIN_PORT and pktinfo.dst_port < MAX_PORT then
		id_port = pktinfo.dst_port
	end
	print("id_port ".. id_port)
	
	
	-- YYYY_MM_DD-hh_mm
	id_date = os.date("%Y_%m_%d-%H_%M", math.floor(pktinfo.abs_ts))
	print("id_date" .. id_date)
	
	filename = USER_DIR .. "plugins\\lolkeys\\" .. id_date .. "-" .. id_port .. ".txt"
	
	b64key = ""
	b64keyfile = ""
	content = ""
	file = io.open(filename, "r")
	if file~=nil then
		content = file:read("*all")
		print("Content: " .. content)
		io.close(file)
		b64keyfile = filename
	else
		print("error opening file ".. filename)
		file = io.open(filename, "w")
		if file~=nil then
			file:write("")
			io.close(file)
			b64keyfile = filename
		else
			print("error creating file ".. filename)
			b64keyfile = "Error, could not create " .. filename
		end
	end
	
	if string.len(content) == 24 and string.match(content, "[a-zA-Z0-9%+/]+==") ~= nil then
		print("Valid Key found")
		b64key = content
		b64keyfile = filename
	else
		cmdstring = "cscript.exe /nologo " .. USER_DIR .. "plugins\\GetLoLGameHash.vbs"
		handle = io.popen(cmdstring , "r")
		output = handle:read('*all')
		handle:close()
		print("Output from " .. cmdstring .. ": " .. output)
		if string.len(output) == 24 and string.match(output, "[a-zA-Z0-9%+/]+==") ~= nil then
			print("Valid Key found")
			b64key = output
			b64keyfile = cmdstring
			file = io.open(filename, "w")
			if file~=nil then
				file:write(output)
				io.close(file)
			else
				print("error creating file ".. filename)
			end
		end
	end
	
	bf_Init(b64key)
	
	enet_proto.dissector(tvbuf, pktinfo, root)
	pktinfo.conversation = enet_proto
	
	return false -- yeah just return always false .....
end

-- register the heuristic for udp only:
enet_proto:register_heuristic("udp", heur_dissect_enet)
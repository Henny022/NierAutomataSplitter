state("NieRAutomata", "1.0")
{
	bool isWorldLoaded : 0x18F3978;
	byte playerNameSetStatus : 0x1461B38;
	string32 currentCutscene : 0x1978868, 0x1F4;
	bool isCutscenePlaying : 0x146A1AC;
	bool isLoading : 0x18DD444;
}

state("NieRAutomata", "1.01")
{
	bool isWorldLoaded : 0x110ADC0;
	byte playerNameSetStatus : 0x147B4BC;
	string32 currentCutscene : 0x19925E8, 0x1F4;
	bool isCutscenePlaying : 0x1483974;
	bool isLoading : 0x147BF50;
	string255 phaseName : 0x1101D20, 0x68;
}

init
{
	int moduleSize = modules.First().ModuleMemorySize;
	switch (moduleSize) {
		case 113471488:
			version = "1.0";
			break;
		case 106266624:
			version = "1.01";
			break;
	}
	print("ModuleMemorySize: " + modules.First().ModuleMemorySize.ToString());
}

startup
{
	settings.Add("usePhaseNameBasedStart", false, "Alternative Auto-start (BETA)");
	settings.SetToolTip("usePhaseNameBasedStart", "** Experimental **\n\n"
	+ "Works with NG Start Game and NG+ Chapter Select to 01-01\n"
	+ "Overrides 'Detect New Game for auto-start'\n\n"
	+ "Note: may need timer offset adjusted\n"
	+ "Note: Only supported in version 1.01");

	settings.Add("detectNewGame", true, "Detect New Game for auto-start");
	settings.SetToolTip("detectNewGame", "disabling this will make the auto-start work on chapterselect for NG+, but it will also make it work at a lot of other places");
	settings.Add("startAfterCutscene", false, "auto-start after cutscenes");
	settings.SetToolTip("startAfterCutscene", "usefull for testing");
	settings.Add("splitAnyCutscene", false, "split on any cutscenes");
	settings.SetToolTip("splitAnyCutscene", "usefull for testing");
	
	settings.Add("splits"          , true , "Splits");
	settings.Add("AB"              , true , "Ending [A/B]", "splits");
	settings.Add("prologue"        , true , "Prologue", "AB");
	settings.Add("movie/ev0010.usm", true , "[A] Crash", "prologue");
	settings.Add("movie/ev0030.usm", true , "[A] Marx 1 Start", "prologue");
	settings.Add("movie/ev0040.usm", false, "[B] Oil Machine End", "prologue");
	settings.Add("movie/ev0050.usm", false, "[B] Marx 1 End", "prologue");
	settings.Add("movie/ev0060.usm", true , "[A] Marx 1 End", "prologue");

	settings.Add("00_85_A_RobotM_Pro_2ndArea" , false, "[A] Silo 2 End (BETA)", "prologue"); // Phase Name Split
	settings.Add("00_90_A_RobotM_Pro_3rdArea" , false, "[A] Silo 3 Start (BETA)", "prologue"); // Phase Name Split
	settings.Add("00_95_A_RobotM_Pro_lastArea", false, "[A] Silo 3 End (BETA)", "prologue"); // Phase Name Split

	settings.Add("movie/ev0070.usm", true , "[A] Marx 2 Start", "prologue");
	settings.Add("movie/ev0080.usm", true , "[A] Engels Start", "prologue");
	settings.Add("movie/ev0090.usm", true , "[A] Engels Missiles", "prologue");
	settings.Add("movie/ev0092.usm", false, "[B] Engels Missiles", "prologue");
	settings.Add("movie/ev0110.usm", false, "[A] Engels ninjas Start", "prologue");
	settings.Add("movie/ev0120.usm", true , "[A/B] Engels Final phase Start", "prologue");
	settings.Add("movie/ev0140.usm", true , "[A/B] Prologue End", "prologue");
	settings.Add("desert"          , true , "Desert", "AB");
	settings.Add("movie/ev0160.usm", false, "[A] Glory to Mankind", "desert");
	settings.Add("movie/ev0170.usm", false, "[A] 5012 AD", "desert");
	settings.Add("movie/ev0190.usm", false, "[A/B] Post Setup", "desert");
	settings.Add("movie/ev0200.usm", true , "[A] Leaving Bunker", "desert");
	settings.Add("movie/evb200.usm", false, "[B] Leaving Bunker", "desert");
	settings.Add("movie/ev0210.usm", true , "[A] City Ruins Discovery", "desert");
	settings.Add("movie/ev0220.usm", true , "[A] Resistance Camp Discovery", "desert");

	settings.Add("50_AB_Desert_temple", false, "[A] Anemone Desert Quest (BETA)", "desert"); // Phase Name Split
	settings.Add("51_AB_MainDesert"   , false, "[A/B] Desert Tunnel (BETA)", "desert"); // Phase Name Split

	settings.Add("movie/ev0225.usm", false, "[A] Desert Discovery", "desert");
	settings.Add("movie/ev0230.usm", false, "[B] [PB] Spirit of Fire", "desert");
	settings.Add("movie/ev0240.usm", true , "[A] Housing District", "desert");
	settings.Add("movie/ev0250.usm", true , "[A/B] Adam 1 Start", "desert");
	settings.Add("movie/ev0260.usm", true , "[A] Adam 1 End", "desert");
	settings.Add("movie/ev0262.usm", true , "[B] Adam 1 End", "desert");

	settings.Add("park"            , true , "Amusement Park", "AB");
	settings.Add("movie/ev0280.usm", false, "[B] [PB] Treasured Items", "park");
	settings.Add("70_AB_Amusement_Park", false, "[A/B] Amusement Park Sewer Exit (BETA)", "park"); // Phase Name Split
	settings.Add("movie/ev0290.usm", false, "[A] Amusement Park Discovery", "park");
	// settings.Add("70_10_AB_Park_Tank", false,   "[A/B] Let's Play (BETA)", "park"); // Phase Name Split
	settings.Add("movie/ev0300.usm", true , "[A/B] Beauvoir Start", "park");
	settings.Add("movie/ev0310.usm", true , "[A/B] Beauvoir Hacking", "park");
	settings.Add("movie/ev0320.usm", true , "[A] Beauvoir End", "park");
	settings.Add("movie/ev0322.usm", true , "[B] Beauvoir Fight Finish", "park");
	settings.Add("movie/ev0323.usm", false, "[B] Beauvoir Dies", "park");

	settings.Add("ruins"           , true , "Devastated Ruins", "AB");
	settings.Add("movie/ev0325.usm", true , "[A] Pascal's Village", "ruins");
	settings.Add("90_00_AB_Ruined_City", false, "[A/B] City Engels Start (BETA)", "ruins"); // Phase Name Split
	settings.Add("movie/ev0330.usm", true , "[A/B] City Engels End", "ruins");
	settings.Add("movie/ev0340.usm", false, "[A/B] Negotiations Start", "ruins");
	settings.Add("movie/ev0350.usm", true , "[A] Negotiations Finish", "ruins");
	settings.Add("movie/ev0352.usm", true , "[B] Negotiations Finish", "ruins");
	settings.Add("movie/ev0360.usm", false, "[B] [PB] Parenticide", "ruins");

	settings.Add("forest"          , true , "Forest", "AB");
	settings.Add("movie/ev0370.usm", true , "[A/B] Commercial Facility (Emil)", "forest");
	settings.Add("movie/ev0380.usm", true , "[A] Forest Discovery", "forest");
	settings.Add("movie/ev0390.usm", true , "[A/B] A2 Start", "forest");
	settings.Add("movie/ev0400.usm", true , "[A/B] A2 End", "forest");
	settings.Add("movie/ev0410.usm", false, "[B] [PB] The Kind King", "forest");

	settings.Add("floodedCity"     , true , "Flooded City", "AB");
	settings.Add("movie/ev0420.usm", false, "[B] [PB] In the Deep Sea", "floodedCity");
	settings.Add("movie/ev0430.usm", true , "[A] Flooded City Discovery", "floodedCity");
	settings.Add("movie/ev0440.usm", true , "[A/B] Grun Start", "floodedCity");
	settings.Add("movie/ev0450.usm", true , "[A/B] Grun \"Laser\"", "floodedCity");
	settings.Add("movie/ev0460.usm", false, "[A/B] Grun Mortar Hit (not triggered)", "floodedCity");
	settings.Add("movie/ev0470.usm", true , "[A/B] Grun After Mortar (double split)", "floodedCity");
	settings.Add("movie/ev0475.usm", false, "[B] Grun Missile Launch", "floodedCity");
	settings.Add("movie/ev0482.usm", true , "[A] Grun Fight Finish ", "floodedCity");
	settings.Add("movie/ev0483.usm", true , "[B] Grun Fight Finish", "floodedCity");
	settings.Add("movie/ev0490.usm", false, "[A] Post Grun reboot", "floodedCity");
	settings.Add("copiedCity"      , true , "Copied City", "AB");
	settings.Add("movie/ev0500.usm", false, "[B] [PB] A Reason to Live", "copiedCity");
	settings.Add("movie/ev0502.usm", false, "[B] A Reason to Live + Adam kill", "copiedCity");
	settings.Add("movie/ev0510.usm", true , "[A] Copied City Discovery", "copiedCity");
	settings.Add("movie/ev0520.usm", true , "[A] Adam 2 Phase 1 Start", "copiedCity");
	settings.Add("movie/ev0525.usm", true , "[A] Adam 2 Phase 2 Start", "copiedCity");
	settings.Add("movie/ev0530.usm", true , "[A] Adam 2 Phase 3 Start", "copiedCity");
	settings.Add("movie/ev0540.usm", false, "[A] Adam 2 End", "copiedCity");
	settings.Add("movie/ev0550.usm", true , "[A/B] Copied City Finish", "copiedCity");
	settings.Add("movie/ev0552.usm", true , "[] Copied City Finish", "copiedCity");
	settings.Add("factory"         , true , "Factory", "AB");
	settings.Add("movie/ev0560.usm", false, "[B] 9S awakens", "factory");
	settings.Add("movie/ev0570.usm", true , "[A] Mooks Start", "factory");
	settings.Add("movie/ev0580.usm", true , "[A/B] So-Shi End", "factory");
	settings.Add("movie/ev0590.usm", false, "[B] [PB] Together", "factory");
	settings.Add("movie/ev0600.usm", false, "[B] YoRHa truth revealed", "factory");
	settings.Add("movie/ev0610.usm", true , "[A] Factory End", "factory");
	settings.Add("movie/ev0612.usm", false, "[B] Factory End", "factory");
	settings.Add("endgame"         , true , "Endgame", "AB");
	settings.Add("movie/ev0620.usm", false, "[B] 9S departs", "factory");
	settings.Add("movie/ev0630.usm", true , "[A] Burning Resistance Camp", "endgame");
	settings.Add("movie/ev0642.usm", true , "[A] Boku-Shi End", "endgame");
	settings.Add("movie/ev0650.usm", true , "[B] Boku-Shi Fight Finish", "endgame");
	settings.Add("movie/ev0655.usm", true , "[A/B] Core #1 End", "endgame");
	settings.Add("movie/ev0660.usm", true , "[A/B] Eve Start", "endgame");
	settings.Add("movie/ev0670.usm", true , "[A/B] Eve Phase 3 Start", "endgame");
	settings.Add("movie/ev0680.usm", false, "[A] Eve End", "endgame");
	settings.Add("movie/ev0682.usm", false, "[B] Eve End", "endgame");
	settings.Add("movie/ev0693.usm", true , "[A] flowers for m[A]schines", "endgame");
	settings.Add("movie/ev0694.usm", true , "[B] or not to [B]e", "endgame");
	settings.Add("movie/ev0710.usm", false, "[] Error in debug build", "endgame");
	settings.Add("movie/ev0720.usm", false, "[C] Preview", "endgame");
	
	settings.Add("CD"              , true , "Ending [C/D]", "splits");
	settings.Add("attack"          , true , "All out Attack", "CD");
	settings.Add("movie/ev0730.usm", false, "[C/D] Beginning attack", "attack");
	settings.Add("movie/ev0740.usm", false, "[C/D] 2B leaves bunker", "attack");
	settings.Add("movie/ev0750.usm", false, "[C/D] 2B arrives", "attack");
	settings.Add("movie/ev0760.usm", false, "[C/D] Saved all Squads", "attack");
	settings.Add("movie/ev0770.usm", false, "[C/D] Virus takes over", "attack");
	settings.Add("movie/ev0780.usm", false, "[C/D] Virus took over", "attack");
	settings.Add("movie/ev0790.usm", false, "[C/D] Deathwarp to bunker", "attack");
	settings.Add("movie/ev0792.usm", false, "[C/D] Deathwarp arrived", "attack");
	settings.Add("movie/ev0810.usm", false, "[C/D] Bunker takeover", "attack");
	settings.Add("movie/ev0820.usm", false, "[C/D] Commander infected", "attack");
	settings.Add("movie/ev0830.usm", true , "[C/D] Bunker Finish", "attack");
	settings.Add("movie/ev0835.usm", true , "[C/D] 2B crashing", "attack");
	settings.Add("movie/ev0840.usm", false, "[C/D] 2B saved by A2", "attack");
	settings.Add("movie/ev0850.usm", false, "[C/D] 2B killed by A2", "attack");
	settings.Add("movie/ev0855.usm", false, "[C/D] Oh... Nines...", "attack");
	settings.Add("hegel"           , true , "Memories of Sand", "CD");
	settings.Add("movie/ev0860.usm", false, "[C/D] A2 awakes", "hegel");
	settings.Add("movie/ev0870.usm", false, "[C/D] Hegel Start", "hegel");
	settings.Add("movie/ev0875.usm", true , "[C/D] Hegel Finish", "hegel");
	settings.Add("movie/ev0880.usm", false, "[C/D] Hegel Hacking Finish", "hegel");
	settings.Add("meatbox"         , true , "Meat Box", "CD");
	settings.Add("movie/ev0900.usm", false, "[C/D] 9S awakes", "meatbox");
	settings.Add("movie/ev0910.usm", false, "[C/D] Meat Box Discovery", "meatbox");
	settings.Add("movie/ev0920.usm", false, "[C/D] Meat Box activating", "meatbox");
	settings.Add("movie/ev0930.usm", false, "[C/D] Help...me...", "meatbox");
	settings.Add("movie/ev0940.usm", true , "[C/D] Meat Box Finish", "meatbox");
	settings.Add("pascal"          , true , "Pascal's Despair", "CD");
	settings.Add("movie/ev0950.usm", false, "[C/D] Village attacked", "pascal");
	settings.Add("movie/ev0960.usm", false, "[C/D] Pascal Engels Start", "pascal");
	settings.Add("movie/ev0970.usm", false, "[C/D] Pascal Engels Finish", "pascal");
	settings.Add("movie/ev0935.usm", true , "[C/D] Pascal Finish", "pascal");
	settings.Add("soulbox"         , true , "Soul Box", "CD");
	settings.Add("movie/ev0980.usm", false, "[C/D] Tower Discovery", "soulbox");
	settings.Add("movie/ev0990.usm", false, "[C/D] Soul Box Discovery", "soulbox");
	settings.Add("movie/ev1000.usm", false, "[C/D] Soul Box Final Start", "soulbox");
	settings.Add("movie/ev1010.usm", true , "[C/D] Soul Box Finish", "soulbox");
	settings.Add("godbox"          , true , "God Box", "CD");
	settings.Add("movie/ev1020.usm", false, "[C/D] post Soul Box Repairs", "godbox");
	settings.Add("movie/ev1030.usm", false, "[C/D] God Box Discovery", "godbox");
	settings.Add("movie/ev1040.usm", false, "[C/D] 21B", "godbox");
	settings.Add("movie/ev1050.usm", false, "[C/D] 21B dead", "godbox");
	settings.Add("movie/ev1060.usm", true , "[C/D] Auguste dead", "godbox");
	settings.Add("movie/ev1070.usm", true , "[C/D] God Box Finish", "godbox");
	settings.Add("tower"           , true , "Tower", "CD");
	settings.Add("movie/ev1090.usm", false, "[C/D] Twin Support", "tower");
	settings.Add("movie/ev1100.usm", false, "[C/D] Tower hack finish", "tower");
	settings.Add("movie/ev1120.usm", false, "[C/D] 2Bs", "tower");
	settings.Add("movie/ev1125.usm", true , "[C/D] 2B Clones Finish", "tower");
	settings.Add("movie/ev1140.usm", false, "[C/D] Library Discovery", "tower");
	settings.Add("movie/ev1150.usm", false, "[C/D] Ko-Shi Library", "tower");
	settings.Add("movie/ev1160.usm", false, "[C/D] 9S awakens", "tower");
	settings.Add("movie/ev1180.usm", false, "[C/D] 9S red girls finished", "tower");
	settings.Add("movie/ev1185.usm", false, "[C/D] 9S Tower Flightunit", "tower");
	settings.Add("movie/ev1190.usm", true , "[C/D] A2 Red Girls Finish", "tower");
	//settings.Add("movie/ev1180.usm", false, "[C/D] Ko-Shi & Ro-Shi start", "tower"); // TODO duplicate?
	settings.Add("movie/ev1210.usm", true , "[C/D] Ko-Shi & Ro-Shi Finish", "tower");
	settings.Add("movie/ev1220.usm", false, "[C/D] pre 9S/A2 fight", "tower");
	settings.Add("movie/ev1230.usm", false, "[D] A2 dead", "tower");
	settings.Add("movie/ev1232.usm", true , "[D] Ending D Finish Variation 1", "tower");
	settings.Add("movie/ev1233.usm", true , "[D] Ending D Finish Variation 2", "tower");
	settings.Add("movie/ev1234.usm", true , "[D] Ending D Finish Variation 3", "tower");
	settings.Add("movie/ev1235.usm", true , "[D] Ending D Finish Variation 4", "tower");
	settings.Add("movie/ev1240.usm", false, "[C] 9S dead", "tower");
	settings.Add("movie/ev1250.usm", true , "[C] Ending C Finish", "tower");
	settings.Add("movie/ev1237.usm", true , "[C] Ending C post", "tower");
	settings.Add("E"               , true , "Ending [E]", "splits");
	settings.Add("movie/ev1270.usm", true , "[E] Ending E Finish", "E");
	settings.Add("others"          , true , "Others", "splits");
	settings.Add("movie/ev1280.usm", false, "[PB] Memories of War", "others");
	settings.Add("movie/ev1310.usm", false, "[PB] Restraints", "others");
	settings.Add("movie/ev1290.usm", false, "[PB] Escape", "others");
	settings.Add("movie/ev1300.usm", false, "[PB] Revenge", "others");
	settings.Add("movie/ev1400.usm", false, "Main Menu Idle", "others");
	settings.Add("movie/ev1402.usm", false, "Main Menu Idle", "others");
	
	settings.SetToolTip("movie/ev0230.usm", "Picture Book");
	settings.SetToolTip("movie/ev0360.usm", "Picture Book");
	settings.SetToolTip("movie/ev0410.usm", "Picture Book");
	settings.SetToolTip("movie/ev0420.usm", "Picture Book");
	settings.SetToolTip("movie/ev0500.usm", "Picture Book");
	settings.SetToolTip("movie/ev0590.usm", "Picture Book");
	settings.SetToolTip("movie/ev1280.usm", "Picture Book");
	settings.SetToolTip("movie/ev1310.usm", "Picture Book, DLC");
	settings.SetToolTip("movie/ev1290.usm", "Picture Book, DLC");
	settings.SetToolTip("movie/ev1300.usm", "Picture Book, DLC");

	settings.SetToolTip("00_85_A_RobotM_Pro_2ndArea" , "Splits after exiting Silo 2 / approaching bridge\n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("00_90_A_RobotM_Pro_3rdArea" , "Splits in corridor before entering Silo 3\n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("00_95_A_RobotM_Pro_lastArea", "Splits after exiting Silo 3 / approaching Engels \n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("50_AB_Desert_temple"        , "Splits when accepting Anemone's Quest after Trader Quests\n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("51_AB_MainDesert"           , "Splits when objective changes in desert tunnel (OOB or in-bounds)\n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("70_AB_Amusement_Park"       , "Splits when exiting sewers towards Amusement Park\n" + "Note: Only supported in version 1.01");
	// settings.SetToolTip("70_10_AB_Park_Tank"         , "Splits when hitting 'Tank' (Let's Play) trigger\n" + "Note: Only supported in version 1.01");
	settings.SetToolTip("90_00_AB_Ruined_City"       , "Splits after delivering filter to Pascal / when City Engels attacks\n" + "Note: Only supported in version 1.01");

	vars.PreviousPhaseName = "UNDEF";
}

start
{
	if (version == "1.01" && settings["usePhaseNameBasedStart"])
	{
		if (current.phaseName == "00_30_A_RobotM_Prologue_STG1" && vars.PreviousPhaseName == "START")
		{
			return true;
		}
	}
	else
	{
		// Thanks Kate for this auto-start logic
		if ((current.playerNameSetStatus == 1 || !settings["detectNewGame"]) && current.isWorldLoaded && !old.isWorldLoaded)
		{
			return true;
		}
		
		if(settings["startAfterCutscene"] && old.isCutscenePlaying && !current.isCutscenePlaying)
		{
			return true;
		}
	}
}

split
{
	if(current.isCutscenePlaying && !old.isCutscenePlaying)
	{
		return (settings.ContainsKey(current.currentCutscene) && settings[current.currentCutscene]) || settings["splitAnyCutscene"];
	}

	if (version == "1.01") {
		// Loading screens set phaseName to empty string
		if (current.phaseName.Length == 0 && old.phaseName.Length > 0)
		{
			vars.PreviousPhaseName = old.phaseName;
		}

		if (current.phaseName != vars.PreviousPhaseName && current.phaseName != old.phaseName && current.phaseName.Length > 0)
		{
			print("LiveSplit Debug - Phase change: " + current.phaseName);
			return settings.ContainsKey(current.phaseName) && settings[current.phaseName];
		}
	}
}

isLoading
{
	return current.isLoading;
}

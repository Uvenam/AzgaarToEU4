#include "../UVEP/globals.h"

const std::vector<std::string> AZGAAR_Government_Forms_Monarchy = {
	"Beylik",
	"Despotate",
	"Dominion",
	"Duchy",
	"Emirate",
	"Empire",
	"Horde",
	"Grand Duchy",
	"Heptarchy",
	"Khaganate",
	"Khanate",
	"Kingdom",
	"Marches",
	"Principality",
	"Satrapy",
	"Shogunate",
	"Sultanate",
	"Tsardom",
	"Ulus",
	"Viceroyalty"
};
const std::vector<std::string> AZGAAR_Government_Forms_Republic = {

	"Chancellery",
	"City-state",
	"Diarchy",
	"Federation",
	"Free City",
	"Most Serene Republic",
	"Oligarchy",
	"Protectorate",
	"Republic",
	"Tetrarchy",
	"Trade Company",
	"Triumvirate"
};
const std::vector<std::string> AZGAAR_Government_Forms_Union = {
	"Confederacy",
	"Confederation",
	"Conglomerate",
	"Commonwealth",
	"League",
	"Union",
	"United Hordes",
	"United Kingdom",
	"United Provinces",
	"United Republic",
	"United States",
	"United Tribes"
};
const std::vector<std::string> AZGAAR_Government_Forms_Theocracy = {
	"Bishopric",
	"Brotherhood",
	"Caliphate",
	"Diocese",
	"Divine Duchy",
	"Divine Grand Duchy",
	"Divine Principality",
	"Divine Kingdom",
	"Divine Empire",
	"Eparchy",
	"Exarchate",
	"Holy State",
	"Imamah",
	"Patriarchate",
	"Theocracy"
};
const std::vector<std::string> AZGAAR_Government_Forms_Anarchy = {

	"Commune",
	"Community",
	"Council",
	"Free Territory",
	"Tribes"
};

const std::vector<std::string> EU4_Government_Forms = {
	"monarchy",
	"republic",
	"tribal",
	"native",
	"theocracy"
};
// Could make this an unordered map
const std::vector<std::string> EU4_Government_Forms_Monarchy = {
	"feudalism_reform",
	"autocracy_reform",
	"plutocratic_reform",
	"indian_sultanate_reform",
	"nayankara_reform",
	"misl_confederacy_reform",
	"rajput_kingdom",
	"negusa_nagast",
	"solomonic_empire",
	//#Specific:
	"grand_duchy_reform",
	"daimyo",
	"indep_daimyo",
	"elective_monarchy",
	"iqta",
	"ottoman_government",
	"prussian_monarchy",
	"austrian_dual_monarchy",
	"principality",
	"tsardom",
	"mamluk_government",
	"feudal_theocracy",
	"celestial_empire",
	"shogunate",
	"english_monarchy",
	"mandala_reform",
	"revolutionary_empire_reform",
	"holy_state_reform",
	"austrian_archduchy_reform",
	"siamese_absolutism",
	"confucian_bureaucracy",
	"musa_rule",
	"mossi_federal_kingdom"

	// Missing some from recent EU4 update (after 1.30.6)

};
// Monarchy -> Level 1 
// government = monarchy
// add_government_reform = ___________
const std::vector<std::string> EU4_Government_Forms_Republic = {
	"oligarchy_reform",
	"merchants_reform",
	"venice_merchants_reform",
	"pirate_republic_reform",
	"noble_elite_reform",
	"free_city",
	"trading_city",
	"ambrosian_republic",
	"veche_republic",
	//# american_republic
	//# federal_republic
	"colonial_government",
	"crown_colony_government",
	"private_enterprise_colony_government",
	"self_governing_colony_government",
	"dutch_republic",
	"peasants_republic",
	"revolutionary_republic_reform",
	"junior_revolutionary_republic_reform",
	"presidential_despot_reform",
	"cossacks_reform",
	"military_dictatorship_reform",
	"signoria_reform",
	"protectorate_parliament_reform",
	"prussian_republic_reform",
	"united_cantons_reform",
	"kongsi_federation",
	"millenarian_theocracy_reform"

	// Missing some from recent EU4 update (after 1.30.6)

};
// Republic -> Level 1
// government = republic
// add_government_reform = ___________
const std::vector<std::string> EU4_Government_Forms_Tribal = {
	"steppe_horde",
	"tribal_federation",			// HAS TO be arab
	"tribal_despotism",
	"tribal_kingdom",
	"siberian_tribe",
	"gond_kingdom",
	"great_mongol_state_reform",	// HAS TO be Mongol Empire
	"stateless_society",
	"polynesian_kingdom",			// HAS TO start with it or complete Polynesian mission centralize the realm, lost if no longer polynesian
	"polynesian_tribe"				// HAS TO start with it, lost if no longer polynesian

	// Missing some from recent EU4 update (after 1.30.6)
};
// Tribal -> Level 1
// government = tribal
// add_government_reform = ___________
const std::vector<std::string> EU4_Government_Forms_Native = {
	"native_chiefdom_reform",
	"native_federation_reform",
	"native_clan_council_reform",
	"native_hereditary_reform"
};
// Native -> Level 1
// government = native
// add_government_reform = ___________
const std::vector<std::string> EU4_Government_Forms_Theocracy = {
	"leading_clergy_reform",
	"monastic_order_reform",
	"papacy_reform",
	"holy_state_reform",
	"united_cantons_reform",

	// Missing some from recent EU4 update (after 1.30.6)
};
// Theocracy -> Level 1
// government = theocracy
// add_government_reform = ___________


std::vector<std::string> AZGAAR_Religions;

const std::vector<std::string> EU4_Religions = {
"catholic",				// christian
"anglican",				// christian
"hussite",				// christian
"protestant",			// christian
"reformed",				// christian
"orthodox",				// christian
"coptic",				// christian
"sunni",				// muslim
"shiite",				// muslim
"ibadi",				// muslim
"buddhism",				// eastern
"vajrayana",			// eastern
"mahayana",				// eastern
"confucianism",			// eastern
"shinto",				// eastern
"hinduism",				// dharmic
"sikhism",				// dharmic
"animism",				// pagan
"shamanism",			// pagan
"totemism",				// pagan
"inti",					// pagan
"nahuatl",				// pagan
"mesoamerican_religion",// pagan
"norse_pagan_reformed",	// pagan
"tengri_pagan_reformed",// pagan
"jewish",				// additional
"zoroastrian"			// additional
};

std::string example_data =
"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},\"properties\":{\"id\":0,\"height\":-109,\"biome\":12,\"type\":\"island\",\"population\":140,\"state\":2,\"province\":3,\"culture\":4,\"religion\":5,\"neighbors\":[1,7,6]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-40.16,51.19],[-42.53,52.2],[-44.21,54.22],[-44.66,57.25],[-44.55,58.26],[-44.1,58.6],[-41.17,58.26],[-36.56,52.65],[-38.14,51.53],[-40.16,51.19]]]},\"properties\":{\"id\":1,\"height\":-29,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[11,10,9,7,0,2,12]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-35.44,52.65],[-36.56,52.65],[-41.17,58.26],[-34.31,60.84],[-33.97,60.5],[-34.65,52.99],[-35.44,52.65]]]},\"properties\":{\"id\":2,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[13,12,1,3]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-30.6,51.76],[-34.65,52.99],[-33.97,60.5],[-27.45,58.04],[-28.57,52.43],[-28.8,52.2],[-30.6,51.76]]]},\"properties\":{\"id\":3,\"height\":-55,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[30,13,2,4,14]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-19.91,57.36],[-22.61,52.32],[-26.33,51.76],[-28.57,52.43],[-27.45,58.04],[-24.52,59.94],[-19.91,57.36]]]},\"properties\":{\"id\":4,\"height\":-88,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[16,15,14,3]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-55.12,47.94],[-65.7,49.29],[-67.5,52.99],[-63.79,56.02],[-56.92,56.35],[-54.9,48.17],[-55.12,47.94]]]},\"properties\":{\"id\":5,\"height\":-88,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[19,18,17,6]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-52.76,48.5],[-54.9,48.17],[-56.92,56.35],[-56.25,56.8],[-50.62,52.65],[-50.4,51.64],[-52.76,48.5]]]},\"properties\":{\"id\":6,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[8,19,5,0,7]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-47.25,49.85],[-50.4,51.64],[-50.62,52.65],[-44.66,57.25],[-44.21,54.22],[-47.25,49.85]]]},\"properties\":{\"id\":7,\"height\":-55,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[9,8,6,0,1]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-48.26,47.38],[-50.06,46.93],[-52.76,48.5],[-50.4,51.64],[-47.25,49.85],[-47.14,48.84],[-48.26,47.38]]]},\"properties\":{\"id\":8,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[22,21,19,6,7,9]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-45.56,48.17],[-47.14,48.84],[-47.25,49.85],[-44.21,54.22],[-42.53,52.2],[-43.42,48.62],[-45.56,48.17]]]},\"properties\":{\"id\":9,\"height\":-9,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[24,22,8,7,1,10]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-40.16,51.19],[-41.17,47.27],[-43.42,48.62],[-42.53,52.2],[-40.16,51.19]]]},\"properties\":{\"id\":10,\"height\":-9,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[1,11,24,9]}}]}";
const std::string example_snippet =
"{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},\"properties\":{\"id\":0,\"height\":-109,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[1,7,6]}}";

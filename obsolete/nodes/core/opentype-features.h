#ifndef NODES_CORE_OT_FEATURES_H
#define NODES_CORE_OT_FEATURES_H

#include <string>
#include <vector>
#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb-ft.h>
#include FT_FREETYPE_H


// #define TEXT_START HB_FEATURE_GLOBAL_START
// #define TEXT_END HB_FEATURE_GLOBAL_END

struct ot_feat_desc_t {
    char* tag;
    unsigned int value;
    unsigned int start;
    unsigned int end;
};

hb_feature_t* get_hb_features(ot_feat_desc_t* descs, unsigned int n) {

    hb_feature_t* feats = (hb_feature_t*)malloc(sizeof(hb_feature_t) * n);

    for(int i=0; i<n; i++) {
        feats[i].tag = HB_TAG(descs[i].tag[0], descs[i].tag[1], descs[i].tag[2], descs[i].tag[3]);
        feats[i].start = descs[i].start;
        feats[i].end = descs[i].end;
        feats[i].value = descs[i].value;
    }

    return feats;
}

// liga 1 0 -1 kern 1 0 -1 
std::vector<hb_feature_t> parse_features(std::string values) {
  
    char* v = (char*)malloc(sizeof(char) * values.length());
    for(int i=0; i<values.length(); i++) v[i] = values[i];
    char * pch;

    pch = strtok (v," ");


    int i=0;
    char* tag;
    unsigned int value;
    unsigned int start;
    unsigned int end;

    std::vector<hb_feature_t> feats = std::vector<hb_feature_t>();

    while (pch != NULL)
    {
        if(i%4 == 0) tag = pch;
        else if(i%4 == 1) value = atoi(pch);
        else if(i%4 == 2) start = atoi(pch);
        else if(i%4 == 3) {
            end = atoi(pch);
            hb_feature_t f = {};
    
            // printf("tag: %c\n", tag[0]);
            // printf("tag: %c\n", tag[1]);
            // printf("tag: %c\n", tag[2]);
            // printf("tag: %c\n", tag[3]);

            f.tag = HB_TAG(tag[0], tag[1], tag[2], tag[3]);
            f.start = start;
            f.end = end;
            f.value = 1;
            feats.push_back(f);
        }

        i++;
        pch = strtok (NULL, " ");
    }

    // for(auto feat: feats) {
    //     printf("tag: %u\n", feat.tag);
    //     printf("value: %u\n", feat.value);
    //     printf("start: %u\n", feat.start);
    //     printf("end: %u\n", feat.end);
    // }

    return feats;
}

/*
    hb_feature_t* userfeatures = (hb_feature_t*)malloc(sizeof(hb_feature_t)*n_feat);
    userfeatures[0].tag = HB_TAG('d','l','i','g');
    userfeatures[0].value = 1;
    userfeatures[0].start = HB_FEATURE_GLOBAL_START;
    userfeatures[0].end = HB_FEATURE_GLOBAL_END;

    userfeatures[1].tag = HB_TAG('k','e','r','n');
    userfeatures[1].value = 1;
    userfeatures[1].start = HB_FEATURE_GLOBAL_START;
    userfeatures[1].end = HB_FEATURE_GLOBAL_END;

    userfeatures[2].tag = HB_TAG('l','i','g','a');
    userfeatures[2].value = 1;
    userfeatures[2].start = HB_FEATURE_GLOBAL_START;
    userfeatures[2].end = HB_FEATURE_GLOBAL_END;

    userfeatures[3].tag = HB_TAG('c','l','i','g');
    userfeatures[3].value = 1;
    userfeatures[3].start = HB_FEATURE_GLOBAL_START;
    userfeatures[3].end = HB_FEATURE_GLOBAL_END;

    userfeatures[4].tag = HB_TAG('f','r','a','c');
    userfeatures[4].value = 1;
    userfeatures[4].start = HB_FEATURE_GLOBAL_START;
    userfeatures[4].end = HB_FEATURE_GLOBAL_END;

    userfeatures[5].tag = HB_TAG('d','i','s','t');
    userfeatures[5].value = 1;
    userfeatures[5].start = HB_FEATURE_GLOBAL_START;
    userfeatures[5].end = HB_FEATURE_GLOBAL_END;

    userfeatures[6].tag = HB_TAG('d','n','o','m');
    userfeatures[6].value = 0;
    userfeatures[6].start = HB_FEATURE_GLOBAL_START;
    userfeatures[6].end = HB_FEATURE_GLOBAL_END;

    userfeatures[7].tag = HB_TAG('c','u','r','s');
    userfeatures[7].value = 1;
    userfeatures[7].start = HB_FEATURE_GLOBAL_START;
    userfeatures[7].end = HB_FEATURE_GLOBAL_END;

    userfeatures[8].tag = HB_TAG('c','c','m','p');
    userfeatures[8].value = 1;
    userfeatures[8].start = HB_FEATURE_GLOBAL_START;
    userfeatures[8].end = HB_FEATURE_GLOBAL_END;

    userfeatures[9].tag = HB_TAG('a','f','r','c');
    userfeatures[9].value = 0;
    userfeatures[9].start = HB_FEATURE_GLOBAL_START;
    userfeatures[9].end = HB_FEATURE_GLOBAL_END;

    userfeatures[10].tag = HB_TAG('o','r','d','n');
    userfeatures[10].value = 1;
    userfeatures[10].start = HB_FEATURE_GLOBAL_START;
    userfeatures[10].end = HB_FEATURE_GLOBAL_END;


    userfeatures[11].tag = HB_TAG('s','a','l','t');
    userfeatures[11].value = 1;
    userfeatures[11].start = HB_FEATURE_GLOBAL_START;
    userfeatures[11].end = HB_FEATURE_GLOBAL_END;

    userfeatures[12].tag = HB_TAG('n','u','m','r');
    userfeatures[12].value = 0;
    userfeatures[12].start = HB_FEATURE_GLOBAL_START;
    userfeatures[12].end = HB_FEATURE_GLOBAL_END;

    userfeatures[13].tag = HB_TAG('s','s','t','y');
    userfeatures[13].value = 2;
    userfeatures[13].start = HB_FEATURE_GLOBAL_START;
    userfeatures[13].end = HB_FEATURE_GLOBAL_END;

    userfeatures[14].tag = HB_TAG('m','a','t','h');
    userfeatures[14].value = 1;
    userfeatures[14].start = HB_FEATURE_GLOBAL_START;
    userfeatures[14].end = HB_FEATURE_GLOBAL_END;

    userfeatures[15].tag = HB_TAG('c','a','l','t');
    userfeatures[15].value = 1;
    userfeatures[15].start = HB_FEATURE_GLOBAL_START;
    userfeatures[15].end = HB_FEATURE_GLOBAL_END;

    userfeatures[16].tag = HB_TAG('s','u','b','s');
    userfeatures[16].value = 1;
    userfeatures[16].start = HB_FEATURE_GLOBAL_START;
    userfeatures[16].end = HB_FEATURE_GLOBAL_END;

    userfeatures[17].tag = HB_TAG('i','t','a','l');
    userfeatures[17].value = 1;
    userfeatures[17].start = HB_FEATURE_GLOBAL_START;
    userfeatures[17].end = HB_FEATURE_GLOBAL_END;

    userfeatures[18].tag = HB_TAG('s','i','n','f');
    userfeatures[18].value = 1;
    userfeatures[18].start = HB_FEATURE_GLOBAL_START;
    userfeatures[18].end = HB_FEATURE_GLOBAL_END;
*/
#endif
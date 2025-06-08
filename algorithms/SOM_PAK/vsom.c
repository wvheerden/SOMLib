//./vsom -din ~/simulations/iris/convert/sims/x20_y20/sets/iris.txt.0.train -vin ~/simulations/iris/convert/sims/x20_y20/sets/iris.txt.0.test -cin iris.20_20.map -cout iris_test.trained.map -lrate 0.5 -lratedecay 100 -radius 10 -radiusdecay 10 -rand 0

/************************************************************************
 *                                                                      *
 *  Program package 'som_pak':                                          *
 *                                                                      *
 *  vsom.c                                                              *
 *  -Visualization Self-Organizing Map                                  *
 *                                                                      *
 *  Version 3.0                                                         *
 *  Date: 1 Mar 1995                                                    *
 *                                                                      *
 *  NOTE: This program package is copyrighted in the sense that it      *
 *  may be used for scientific purposes. The package as a whole, or     *
 *  parts thereof, cannot be included or used in any commercial         *
 *  application without written permission granted by its producents.   *
 *  No programs contained in this package may be copied for commercial  *
 *  distribution.                                                       *
 *                                                                      *
 *  All comments  concerning this program package may be sent to the    *
 *  e-mail address 'lvq@cochlea.hut.fi'.                                *
 *                                                                      *
 ************************************************************************/

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include "lvq_pak.h"
#include "som_rout.h"
#include "datafile.h"


// removed -rlen - alpha_type
static char *usage[] = {
	"vsom - teach self-organizing map\n",
	"Required parameters:\n",
	"  -cin filename         initial codebook file\n",
	"  -din filename         training data\n",
  "  -vin filename         validation data\n",                // added
	"  -cout filename        output codebook filename\n",
	"  -lrate double          initial learning rate value\n",    // changed name
	"  -lratedecay double     learning rate decay constant\n",   // added
	"  -radius double         initial radius of neighborhood\n",
	"  -radiusdecay double    radius decay constant\n",          // added
	"Optional parameters:\n",
  "  -qetype 1             another way to calculate the quantisation error\n"
	"  -rand integer         seed for random number generator. 0 is current time\n",
	"  -fixed                use fixed points\n",
	"  -weights              use weights\n",
	"  -buffer integer       buffered reading of data, integer lines at a time\n",
	"  -snapfile filename    snapshot filename\n",
	"  -selfuncs name        select a set of functions\n",
	"  -snapinterval integer interval between snapshots\n",
	NULL
};

int
main (int argc, char **argv)
{
	char *in_data_file;
  char *in_validation_file;   // added
	char *in_code_file;
	char *out_code_file;
	char *snapshot_file;
	//char *alpha_s, *rand_s;
  char *rand_s;
	struct entries *data_training = NULL, *data_training_error = NULL, *data_validation_error = NULL, *codes = NULL;
	long randomize;
	int fixed;
	int weights;
	struct teach_params params;
	long buffer = 0;
	long snapshot_interval;
	struct snapshot_info *snap = NULL;
	int snap_type;
	struct typelist *type_tmp;

	int error = 0;
	char *funcname = NULL;

/*
int i;
init_random(0);
for (i = 0; i < 50000; i++) {
  printf("%d\n", orand());
}
exit(0);
*/

	data_training = data_training_error = data_validation_error = codes = NULL;

	global_options (argc, argv);
	if (extract_parameter (argc, argv, "-help", OPTION2)) {
		printhelp ();
		exit (0);
	}

	in_data_file = extract_parameter (argc, argv, IN_DATA_FILE, ALWAYS);
  in_validation_file = extract_parameter (argc, argv, IN_VALIDATION_FILE, ALWAYS);

	in_code_file = extract_parameter (argc, argv, IN_CODE_FILE, ALWAYS);
	out_code_file = extract_parameter (argc, argv, OUT_CODE_FILE, ALWAYS);

  /*  removed due to adaptive stopping condition
	params.length =
		oatoi (extract_parameter (argc, argv, RUNNING_LENGTH, ALWAYS), 1);
  */

	params.alpha =
		atof (extract_parameter (argc, argv, TRAINING_ALPHA, ALWAYS));

  // added
  params.alphaDecay =
		atof (extract_parameter (argc, argv, ALPHA_DECAY, ALWAYS));

	params.radius =
		atof (extract_parameter (argc, argv, TRAINING_RADIUS, ALWAYS));

  // added
  params.radiusDecay =
    atof (extract_parameter (argc, argv, TRAINING_RADIUS_DECAY, ALWAYS));

  // added
  params.qmode = oatoi (extract_parameter (argc, argv, QUANTISATION_ERROR_TYPE, OPTION), 0);

	rand_s = extract_parameter (argc, argv, RANDOM, OPTION);
	randomize = oatoi (rand_s, 0);

	fixed = (extract_parameter (argc, argv, FIXPOINTS, OPTION2) != NULL);
	weights = (extract_parameter (argc, argv, WEIGHTS, OPTION2) != NULL);

	buffer = oatoi (extract_parameter (argc, argv, "-buffer", OPTION), 0);

	//alpha_s = extract_parameter (argc, argv, "-alpha_type", OPTION);    removed due to adaptive stopping condition
	funcname = extract_parameter (argc, argv, "-selfuncs", OPTION);

	/* snapshots */
	snapshot_file = extract_parameter (argc, argv, "-snapfile", OPTION);
	snapshot_interval =
		oatoi (extract_parameter (argc, argv, "-snapinterval", OPTION), 0);

	snap_type =
		get_id_by_str (snapshot_list,
									 extract_parameter (argc, argv, "-snaptype", OPTION));


	use_fixed (fixed);
	use_weights (weights);

	label_not_needed (1);

	if (snapshot_interval) {
		if (snapshot_file == NULL) {
			snapshot_file = out_code_file;
			fprintf (stderr, "snapshot file not specified, using '%s'",
							 snapshot_file);
		}
		snap = get_snapshot (snapshot_file, snapshot_interval, snap_type);
		if (snap == NULL)
			exit (1);
	}

	ifverbose (2) {
		fprintf (stderr, "Training entries are read from file %s\n", in_data_file);
    fprintf (stderr, "Validation entries are read from file %s\n", in_validation_file);
  }

	data_training = open_entries (in_data_file);
	if (data_training == NULL) {
		fprintf (stderr, "cant open data file '%s'\n", in_data_file);
		error = 1;
		goto end;
	}

  data_training_error = open_entries (in_data_file);
  if (data_training_error == NULL) {
		fprintf (stderr, "cant open data file '%s'\n", in_data_file);
		error = 1;
		goto end;
  }

	data_validation_error = open_entries (in_validation_file);
	if (data_validation_error == NULL) {
		fprintf (stderr, "cant open validation file '%s'\n", in_validation_file);
		error = 1;
		goto end;
	}

	ifverbose (2)
		fprintf (stderr, "Codebook entries are read from file %s\n",
						 in_code_file);
	codes = open_entries (in_code_file);
	if (codes == NULL) {
		fprintf (stderr, "Can't open code file '%s'\n", in_code_file);
		error = 1;
		goto end;
	}

	if (codes->topol < TOPOL_HEXA) {
		fprintf (stderr, "File %s is not a map file\n", in_code_file);
		error = 1;
		goto end;
	}

	if ((data_training->dimension != codes->dimension) || (data_training->dimension != data_validation_error->dimension)) {
		fprintf (stderr, "Data, validation and codebook vectors have different dimensions");
		error = 1;
		goto end;
	}
	
	set_teach_params (&params, codes, data_training, data_training_error, data_validation_error, buffer, funcname);
	set_som_params (&params);
	params.snapshot = snap;

	init_random (randomize);

	// take teaching vectors in random order. Training and validation error sets need not be in random order.
	if (rand_s) {
		data_training->flags.random_order = 1;
  }
  data_training_error->flags.random_order = 0;
  data_validation_error->flags.random_order = 0;

  /*  removed due to adaptive stopping condition
	if (alpha_s) {
		type_tmp = get_type_by_str (alpha_list, alpha_s);
		if (type_tmp->data == NULL) {
			fprintf (stderr, "Unknown alpha type %s\n", alpha_s);
			error = 1;
			goto end;
		}
	} else
		type_tmp = get_type_by_id (alpha_list, ALPHA_LINEAR);
  */

	//params.alpha_type = type_tmp->id;   removed due to adaptive stopping condition
	//params.alpha_func = (ALPHA_FUNC *) type_tmp->data;  removed due to adaptive stopping condition

	codes = som_training (&params);
	
	// print parameter settings
	fprintf(stderr, "Training file              : %s\n", in_data_file);
	fprintf(stderr, "Dimensions                 : %d\n", data_training->dimension);
	fprintf(stderr, "Records                    : %ld\n", data_training->num_entries);
	if (rand_s) {
		if (rand_s[0] == '0') {
			fprintf(stderr, "Random seed used           : Time\n");
		} else {
			fprintf(stderr, "Random seed used           : %s (fixed)\n", rand_s);
		}
	} else {
		fprintf(stderr, "Random seed NOT used\n");
	}
	fprintf(stderr, "\n");
	
	fprintf(stderr, "Validation file            : %s\n", in_validation_file);
	fprintf(stderr, "Dimensions                 : %d\n", data_validation_error->dimension);
	fprintf(stderr, "Records                    : %ld\n", data_validation_error->num_entries);
	fprintf(stderr, "\n");
	
	fprintf(stderr, "Map width                  : %d\n", codes->xdim);
	fprintf(stderr, "Map height                 : %d\n", codes->ydim);
	fprintf(stderr, "Initial learning rate      : %f\n", params.alpha);
	fprintf(stderr, "Learning rate decay factor : %f\n", params.alphaDecay);
	fprintf(stderr, "Initial radius             : %f\n", params.radius);
	fprintf(stderr, "Radius decay factor        : %f\n", params.radiusDecay);
	
	ifverbose (2)
		fprintf (stderr, "Codebook entries are saved to file %s\n",
						 out_code_file);
	save_entries (codes, out_code_file);
end:

	if (data_training)
		close_entries (data_training);
  if (data_training_error)
    close_entries (data_training_error);
  if (data_validation_error)
    close_entries (data_validation_error);
	if (codes)
		close_entries (codes);

	if (snap)
		free_snapshot (snap);

  freerand();

	return (error);
}

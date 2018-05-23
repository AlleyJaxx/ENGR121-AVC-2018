Milestone & objectives:

Thursday Week 1 - 3rd May

    Team Goal by end of week 1: Meet team members, assign roles, discuss design idea
    
    Goals:
    Everyone
     - Discuss design ideas/ roles/ exchange contacts.
     - Setup github repository.
     - Organise next team meeting.
     
        ****Progress:****
        Team Meeting #1: 4th May - In lab (1-3pm) CO145
          - Alex: set up github repository, shared google doc and messenger group chat.
          - Each team member given roles. 
         
         Team Meeting #2: 5th May 4-6pm CO145
         All members present:
          - Alex: worked on 3D marble mount (CAD)
          - James: worked on chassis
          - Kirsty: worked on camera mount
          - Thomas and Adam: checked camera was working and wrote first code for taking/storing pictures. 
          - Team meeting set for Mon 7/5/18 11am-12pm

          Team Meeting #3: 7th May 11am - 12pm CO145 & 1-2pm CO145
          All members present
            - Alex: finished marble mount design in CAD and started 3D printing
            - James: Further work on chassis
            - Kirsty: worked on teams AVC plan
            - Thomas: worked on software design
            - Adam: worked on dev code for basic moment

            Team meeting set for next lab 10th May 1-3pm
            Hardware team may meet between then. Alex and James to organise amongst themselves. 
            
          Hardware meeting: 9th May 11am - 12am CO145
          Alex & James: worked on 3D printing
            - Issues: while leaving mount 3D printing unattended while at lecture, 
                      part went missing when they came back to pick it up. 
                      Managed to find spare mounts instead of reprinting.
                      
                      
                      ***Team uptodate with progress goals set out***

     
After Thursday Week 1 - 4th - 9th May:

    Team Goal by end of week 1: Robot chassis to be built, sensors and camera attached (and working). 
                                Start on software design.
    
    Goals:
    Everyone: Make sure that the github repository is working. Sign Team agreement & finish AVC plan (due 7th May).
     - James & Alex: Finalise hardware design. Have the chassis complete – 3D parts printed (marble and sensor mounts). 
       Base and platforms measured, cut and holes drilled. Wheel mounts and camera mount completed. Complete building 
       of bot prototype.
     - Thomas, Adam & Kirsty: Start on methods and code design.
     - Thomas & Adam: Test camera and sensors are working
     - Kirsty: Organise next team meeting. Update progress and documentation in github, check in on members progress
     
     ****Progress:****
    - AVC Plan submitted 7th May
    - Hardware: main components completed, just a few tweaks to be done with the camera and sensors by end of week 2.
    - Software - basic code dev (moving forward, left, right & backwards). 
    - Various codes committed to github.
     
Thursday Week 2 - 10th – 16th May

    Team Goal by end of week 1: Quadrant 1 & 2 completed
 
    Goals:
    Everyone: Testing and debugging the line following code works. Testing and debugging the codes for quadrant 1 & 2. Start
              on the progress report.
     - Alex & James: Finish any unfinished parts. Test against coding completed, to make sure hardware fits the code. Make
                     any adjustments as needed.
     - Adam: Develop code for basic movement (moving in a straight line, turning, reversing).
     - Thomas: Implement sensor averaging and image processing code (quadrant 2).
     - Kirsty: Develop networking code (quadrant 1). Organise next meeting. Update progress and documentation in github.
               Check in on members progress.
               
        ****Progress:****
        Meeting #4: 10th May - In lab (1-3pm) CO145
        All members present.
        - Alex & James working on sensor mounts, assembly of bot. 
          (Complete: sensor mounts, base, wheels/motors, battery, camera)
        - Adam: Develop code for basic movement (moving in a straight line, turning at different speeds - committed in
                github).
        - Thomas: Implement sensor averaging and image processing code (completed last week, just needs testing) - committed
                  to github. 
        - Kirsty: Developing networking code for quad 1 (opening first gate).

 ***Hardware - main components completed, just a few tweaks to be done with the camera and sensors by end of week 2.*** 
 ***Software - basic code dev (moving forward, left and right). Various codes committed to github.*** 

        Team meeting set for Fri 11/5 12-1pm and 2-3pm

      Meeting #5: 11th May - 1st session (12-1pm), 2nd session (2-3pm) CO145
        (Split sessions due to different members having labs at different times). 
        Each member attended at least one meeting session. 

        Progress: issues with camera no longer working even though was working week one in our testing phase. 
        Tried to problem solve whether is was a hardware or software issue. After a few attempts at retesting 
        the code and commands, and repluging in the camera, it was realised that there was a loose chip on the 
        front of the camera, which solved the issue. 

        Camera was now detected. Tested detection on course (Quad 1). Bot would ver to the right and not follow white line. 
        After printing out the camera readings, realised the camera was not detecting any values and was not producing any
        images. Ran out of time to problem solve further. And had to leave for next session.

        Next meeting set for 11-12pm Monday 14th May.
        
      Meeting #6: 14th May - 11-12pm
        Attended: Alex, Adam, Thomas and Kirsty. Apologies: James

        Issues: camera not producing any images. Checked coding was correct. Figured was an hardware issue. Spoke with
        Arthur who tested our camera and swapped out the wire. Issues solved: damaged wire, most likely caused by not
        switching the bot off before disassembling wire from raspberry Pi. 

        Work to do before Thursday lab:
        Everyone work on individual component and bring together for thursdays lab.
        
      14th May - 2-4pm (Lab work)  
       - Kirsty: Finished network code, committed to github and tested on bot - working. 
       - Thomas: finished follow_line code for Quadrant 2. Committed to github and merged with quad 1 code. 
         Tested on bot - working. Stopped at beginning of quadrant 3. 

                             ****Progress for end of week 2: Quadrant 1 & 2 completed***

Thursday Week 3 - 17th – 23rd May

    Team Goal to be completed by end of week 3: Quadrant 3 & 4 completed

    Goals:
    Everyone: Testing and debugging of quadrant 3 & 4. Finish progress report (Due 21st May). Finishing tweaks on software
              codes.
    - James: Finishing tweaks on robot hardware,
    - Adam & Alex: Develop code for quadrant 3.
    - Kirsty & James: Develop code for stopping at red line and waiting for gate to open (quadrant 4), develop code for
                      quadrant 4 (hugging right wall).
    - Thomas: Main testing and debugging
    - Kirsty: Organise next meeting. Update progress and documentation in github. Check in on members progress.
    
    Meeting #8: 18th May - 2pm onwards CO145
       Attended: Alex, Kirsty, Thomas, James - Apologies: Adam (lab)
         - Thomas and Alex: Worked on quad 3 code and testing. Managed to get the bot successfully through on multiple
                            occasions however not consistently. Made multiple adjustments to code before coming to the
                            conclusion that it was a lighting issues and altered code to be more black sensitive which
                            worked successfully and allowed the bot to move through quad 3 (consistently reaching the end -
                            until the orange tape). 

         - Kirsty and James: Worked on quad 4. James committed code to github.  Worked on code design. How we where going to
                             get bot to detect right wall and hug it while making the correct turns. Agreed that a fourth
                             sensor was to be added to the right back of the bot and the original right sensor to be moved
                             forward to the front right of the bot, allowing the both to keep an equal distance hugging the
                             right wall, with the front sensor to detect the space in front of the bot (if any), and the
                             left sensor to detect an opening on the left side (if any). Remainder of code to be completed
                             Monday and once completed then can be tested. Found spare mount, and redrilled back hole to
                             secure sensor.  

        Next team meeting - Mon 21st 10am-12pm CO145. 
        
    Meeting #9: 21st May 10am - 12pm
    Attended: Alex, Thomas, Adam - Apologies: Kirsty & James
     - Thomas: v_go increased to 120. Kp increased to 120. Left_bias removed temporarily (set to 1) V_go set to 50, Kp set
               to 80 for quadrant 2, goes slower so it is easier to test. Fixed threshold setting code - now sets the
               threshold every frame. If the max < 120 and range between max and min is less than 80, all pixels are
               considered black. If the min>100 and range <150 then all pixels considered white.
               Number of pixels increased to 155 before all pixels on one side are considered white in quadrant 3 code - was
               detecting intersections too frequently. Also added code that would return 0 (go straight) if number of white
               pixels was larger than 200, to prevent the robot from turning randomly after seeing intersections it’s not
               meant to turn down.

                                AVC progress report (individual) due 11.59pm 21/5/18. 
            ****Progress: Quadrant 3 completed & all member now have at least one commit to github****
            
            Still to be done: Finish qudrant 4 code and testing. Testing of all quadrants against all conditions. 
            
Thursday Week 4 - 24th – 31st May

     Team Goal to be completed by end of week 4: Final testing/debugging
     
     Goals:
     Everyone: Testing practice (any last minute debugging)
               Testing happens Tuesday May 29 - Thursday May 31

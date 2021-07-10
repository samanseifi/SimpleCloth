clc
close all

% Getting the initial coordinates of initial configuration
pos_init = dlmread('pos0.csv', ',', 1,0);

% Create Delauny triangles data from the initial configuration
T = delaunay(pos_init(:,2), pos_init(:,3));
pos_old = pos_init;

h0 = figure('Color',[1 1 1]);
axis tight manual % this ensures that getframe() returns a consistent size
gif_filename = 'hanging_cloth.gif';
n = 1;

% Loop through output
for i = 0:10:2000
    
    % Reading through the output files
    filename = sprintf('pos_t%d.000000.csv', i);
    pos_curr = dlmread(filename, ',', 1, 0);
    
    % Calculate displacements
    disp = sqrt((pos_init(:,2) - pos_curr(:,2)).^2 + (pos_init(:,3) - pos_curr(:,3)).^2 + (pos_init(:,4) - pos_curr(:,4)).^2);

    % Corresponds the displacement to nodal data
    h = trisurf(T, pos_curr(:,2), pos_curr(:,3), disp);

    % Get the coloring RGB data of each face according to the displacements
    cd = h.FaceVertexCData;
    
    % Plotting the cloth!
    trisurf(T, pos_curr(:,2), pos_curr(:,3), pos_curr(:,4), cd);
    shading faceted
    
    % Set the color bar
    colormap(jet);
    set(gca,'CLim',[0 10]) %,'XTick',zeros(1,0),'YTick',zeros(1,0),'ZTick', zeros(1,0));
    box(gca, 'on');
  
    % Create zlabel
    zlabel('$z$','FontSize',25,'Interpreter','latex');

    % Create ylabel
    ylabel('$y$','FontSize',25,'Interpreter','latex');

    % Create xlabel
    xlabel('$x$','FontSize',25,'Interpreter','latex');
    
    % Fix the axis!
    zlim([-10 0]);
    xlim([0 15]);
    ylim([0 15]);
    view([30 75 20]);
    
%     hold on;
%     plot3(pos_curr(:,2), pos_curr(:,3), pos_curr(:,4), 'MarkerFaceColor',[0 0.447058823529412 0.741176470588235],...
%     'MarkerEdgeColor',[0 0 0],...
%     'Marker','o',...
%     'LineStyle','none',...
%     'Color',[0 0 0])
%     hold off
    
    % Live plotting!
    drawnow;
    
    % Update!
    pos_old = pos_curr;
    
    % Creating a GIF!
    % **<@{*
    % Capture the plot as an image 
    frame = getframe(h0); 
    im = frame2im(frame); 
    [imind,cm] = rgb2ind(im,256); 
    % **<@}*
 
      % Write to the GIF File 
      if n == 1 
          imwrite(imind,cm,gif_filename,'gif','DelayTime',0.1,'Loopcount',inf); 
      else 
          imwrite(imind,cm,gif_filename,'gif','DelayTime',0.1,'WriteMode','append'); 
      end 
    n = n+1;

end